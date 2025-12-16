#include "pch/pch.h"
#include "SMFPlayer.h"
#include <bit>


namespace
{
	const uint8_t C4_60_NUM{ 0x3C };
	const size_t C4_60_INDEX{ 39 };

	const std::array<float, 88> HZ
	{
		27.500f,  // ラ0
		29.135f,
		30.868f,
		32.703f,
		34.648f,
		36.708f,
		38.891f,
		41.203f,
		43.654f,
		46.249f,
		48.999f,
		51.913f,
		55.000f,
		58.270f,
		61.735f,
		65.406f,
		69.296f,
		73.416f,
		77.782f,
		82.407f,
		87.307f,
		92.499f,
		97.999f,
		103.826f,
		110.000f,
		116.541f,
		123.471f,
		130.813f,
		138.591f,
		146.832f,
		155.563f,
		164.814f,
		174.614f,
		184.997f,
		195.998f,
		207.652f,
		220.000f,
		233.082f,
		246.942f,
		261.626f,
		277.183f,
		293.665f,
		311.127f,
		329.628f,
		349.228f,
		369.994f,
		391.995f,
		415.305f,
		440.000f,
		466.164f,
		493.883f,
		523.251f,
		554.365f,
		587.330f,
		622.254f,
		659.255f,
		698.456f,
		739.989f,
		783.991f,
		830.609f,
		880.000f,
		932.328f,
		987.767f,
		1046.502f,
		1108.731f,
		1174.659f,
		1244.508f,
		1318.510f,
		1396.913f,
		1479.978f,
		1567.982f,
		1661.219f,
		1760.000f,
		1864.655f,
		1975.533f,
		2093.005f,
		2217.461f,
		2349.318f,
		2489.016f,
		2637.020f,
		2793.826f,
		2959.955f,
		3135.963f,
		3322.438f,
		3520.000f,
		3729.310f,
		3951.066f,
		4186.009f,  // ド8
	};

	uint8_t TEST_SMF[]
	{
		// === MThd チャンク (MIDI Header) ===
		0x4D, 0x54, 0x68, 0x64, // MThd (Header Marker)
		0x00, 0x00, 0x00, 0x06, // Length (6 bytes)
		0x00, 0x01,             // Format 1 (Multi-track)
		0x00, 0x02,             // Num Tracks (2)
		0x01, 0xE0,             // Division (480 ticks per quarter note)

		// === MTrk チャンク 0 (テンポ/設定) ===
		0x4D, 0x54, 0x72, 0x6B, // MTrk (Track Marker)
		0x00, 0x00, 0x00, 0x1B, // Length (27 bytes)

		// 0ティック: シーケンス名
		0x00, 0xFF, 0x03, 0x0A, 0x54, 0x65, 0x73, 0x74, 0x20, 0x43, 0x68, 0x6F, 0x72, 0x64, // "Test Chord"

		// 0ティック: テンポ設定 (120 BPM = 500,000 マイクロ秒/四分音符)
		0x00, 0xFF, 0x51, 0x03, 0x07, 0xA1, 0x20,

		// 0ティック: トラック終端
		0x00, 0xFF, 0x2F, 0x00,

		// === MTrk チャンク 1 (ノートデータ) ===
		0x4D, 0x54, 0x72, 0x6B, // MTrk (Track Marker)
		0x00, 0x00, 0x00, 0x24, // Length (36 bytes)

		// 0ティック: 楽器設定 (Ch 1 -> Grand Piano 1)
		0x00, 0xC0, 0x00,

		// 0ティック: NOTE ON (C4 - 60, Velocity 100)
		0x00, 0x90, 0x3C, 0x64,

		// 0ティック: NOTE ON (E4 - 64, Velocity 100)
		0x00, 0x90, 0x40, 0x64,

		// 0ティック: NOTE ON (G4 - 67, Velocity 100)
		0x00, 0x90, 0x43, 0x64,

		// 1920ティック (可変長表現 83 60)
		// NOTE OFF (C4 - 60)
		0x83, 0x60, 0x80, 0x3C, 0x00,

		// 0ティック: NOTE OFF (E4 - 64) (Running Status使用)
		0x00, 0x40, 0x00,

		// 0ティック: NOTE OFF (G4 - 67) (Running Status使用)
		0x00, 0x43, 0x00,

		// 0ティック: トラック終端
		0x00, 0xFF, 0x2F, 0x00
	};
}

SMFPlayer::SMFPlayer(const fs::path& _file) : GameObject
{
	[](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
				.EndSetter()
		.Build();
	}
},
	file_{ _file },
	readCurr_{},
	hTone_{},
	playTime_{},
	toneSampleRateHz_{},
	onNoteCallback_{ [](const Note&){} }
{
}

SMFPlayer::~SMFPlayer()
{
}

void SMFPlayer::Init()
{
	using namespace mtbin;
	using mtbin::util::CompareId;
	using mtbin::util::Reverse;

	smfHeader_ = {};

	std::ifstream smf{ file_, std::ios::binary };

	if (!smf)
	{
		wassert(false && "ファイル読み込み失敗");
		return;
	}

	smf.seekg(0, std::ios_base::end);
	size_t fileSize{ static_cast<size_t>(smf.tellg()) };
	smf.seekg(0, std::ios_base::beg);


	std::vector<Byte> fileBuffer
	{
		std::istreambuf_iterator<char>(smf),
		std::istreambuf_iterator<char>()
	};
	smf.close();  // ファイルは見終わったから閉じる

	BinaryReader br{ fileBuffer.data(), fileBuffer.size() };
	//BinaryReader br{ reinterpret_cast<mtbin::Byte*>(TEST_SMF), sizeof(TEST_SMF) };
	br.Seek(SeekAt::Head);

	std::array<Byte, 4> buff4{};
	std::array<Byte, 2> buff2{};

#pragma region ヘッダチャンク
	if (br.Read(buff4.data(), 4, 4); !CompareId(buff4, "MThd"))
	{
		wassert(false && "ヘッダ不一致");
		return;
	}

	uint32_t headerSize{ br.ReadRev<uint32_t>() };
	LOGFLN("HeaderSize:{}", headerSize);

	uint16_t format{ br.ReadRev<uint16_t>() };
	LOGFLN("Format:{}", format);

	uint16_t truckCount{ br.ReadRev<uint16_t>() };
	LOGFLN("truckCount:{}", truckCount);

	smfTrucks_.resize(truckCount);

	int16_t timeUnit{ br.ReadRev<int16_t>() };
	if (timeUnit < 0)
	{
		wassert("分解能が何分何秒何フレームは対応していないよ");
	}
	smfHeader_.quaterUnit = timeUnit;
	LOGFLN("timeUnit:{}", timeUnit);
#pragma endregion

#pragma region トラックチャンク
	int truckId{ 0 };
	while (br.Current() < br.Size())
	{
		LOGFLN("--------------------truckCount:{} / {}--------------------", truckId, truckCount);
		if (br.Read(buff4.data(), 4, 4); !CompareId(buff4, "MTrk"))
		{
			wassert(false && "トラックヘッダ不一致");
			return;
		}

		uint32_t headerSize{ br.ReadRev<uint32_t>() };
		LOGFLN("HeaderSize:{}", headerSize);

		uint8_t prevStatus{};  // ランニングステータス用
		size_t endOfTruckPos{ br.Current() + headerSize };

		TruckGenerater truckGen{ smfTrucks_.at(truckId), smfHeader_ };

		bool endOfTruckFlag{ false };
		while (br.Current() < endOfTruckPos && !endOfTruckFlag)
		{
			uint64_t delta{ ReadDelta(br) };
			truckGen.AddDeltaTime(delta);
			LOGFLN("DeltaTime:{}", delta);

			uint8_t status{};
			uint8_t peekStatus{ br.Peek<uint8_t>() };
			if (peekStatus < 0x80)  // ランニングステータス対策
			{
				// 0x80未満なら前回のを使う

				if (prevStatus == 0x00)
				{  // でも前回のがなかったらファイルがおかしい
					wassert(false && "ランニングステータスないよ");
					return;
				}

				status = prevStatus;
				LOGFLN("StatusR:{:x}", +status);
			}
			else
			{
				status = br.Read<uint8_t>();
				LOGFLN("Status:{:x}", +status);
			}

			if (status != 0xF0 && status != 0xF7)
			{
				prevStatus = status;  // SystemEx以外はランニングに使える
			}

			if (status == 0xFF)
			{  // メタイベント
				uint8_t subStatus{ br.Read<uint8_t>() };
				LOGFLN("meta");

				switch (subStatus)
				{
				case 0x00:  // シーケンス番号
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint16_t sequenceNumber{ br.ReadRev<uint16_t>() };
					LOGFLN("Sequence:{} size:{}", sequenceNumber, size);
					break;
				}
				case 0x01:
				case 0x02:
				case 0x03:
				case 0x04:
				case 0x05:
				case 0x06:
				case 0x07:
				case 0x08:
				case 0x09:
				case 0x0a:
				case 0x0b:
				case 0x0c:
				case 0x0d:
				case 0x0e:
				case 0x0f:
				{
					int size{ static_cast<int>(ReadDelta(br)) };
					if (size == 0)
					{
						break;
					}
					std::vector<char> textBuffer(size, '\0');
					br.Read(textBuffer.data(), size, size);

					if (subStatus == 0x03)
					{
						truckGen.SetName(textBuffer.data());
					}

					LOGFLN("{:x}:{}", subStatus, textBuffer.data());
					break;
				}
				case 0x20:  // MIDIチャンネルプレフィックス
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint8_t channel{ br.Read<uint8_t>() };
					
					LOGFLN("channel prefix channel{} size{}", channel, size);
					break;
				}
				case 0x21:  // MIDIポートプレフィックス
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint8_t port{ br.Read<uint8_t>() };  // ポート番号

					LOGFLN("port prefix port{} size{}", port, size);
					break;
				}
				case 0x2F:  // トラック最後！
				{
					uint8_t size{ br.Read<uint8_t>() };
					endOfTruckFlag = true;
					break;
				}
				case 0x51:  // テンポの設定
				{
					uint8_t size{ br.Read<uint8_t>() };
					std::array<Byte, 3> buff{};
					br.Read(buff.data(), 3, 3);
					uint32_t tempo
					{
						(static_cast<uint32_t>(buff[0]) << 16) |
						(static_cast<uint32_t>(buff[1]) << 8) |
						(static_cast<uint32_t>(buff[2]) << 0)
					};

					truckGen.SetTempo(tempo);
					LOGFLN("set tempo:{}", tempo);
					break;
				}
				default:
				{
					int size{ static_cast<int>(ReadDelta(br)) };
					std::vector<char> textBuffer(size, '\0');

					br.Read(textBuffer.data(), size, size);
					//LOGFLN("???{:x}:{}", subStatus, textBuffer.data());
					break;
				}
				}
			}
			else if (status == 0xF0 || status == 0xF7)
			{  // システム拡張イベント
				int size{ static_cast<int>(ReadDelta(br)) };

				if (status == 0xF0)
				{
					if (br.Peek<uint8_t>() == 0xF7)
					{
						br.Read<uint8_t>();
						LOGFLN("Skepped 0xF7");
					}
					//size += 1;
				}

				std::vector<char> textBuffer(size, '\0');
				br.Read(textBuffer.data(), size, size);
				LOGFLN("SystemEx size:{}", size);
			}
			else if (0xB0 <= status && status <= 0xBF)
			{  // コントロールチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xB0) };
				uint8_t ccNum{ br.Read<uint8_t>() };
				uint8_t ccValue{ br.Read<uint8_t>() };

				LOGFLN("CC - channel:{}, number:{}, value:{}", channel, ccNum, ccValue);
			}
			else if (0xC0 <= status && status <= 0xCF)
			{  // プログラムチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xC0) };
				uint8_t pcNum{ br.Read<uint8_t>() };

				LOGFLN("PC - channel:{}, number:{}", channel, pcNum);
			}
			else if (0xD0 <= status && status <= 0xDF)
			{  // チャンネルプレッシャー / アフタータッチ
				uint8_t channel{ static_cast<uint8_t>(status - 0xD0) };
				uint8_t cpValue{ br.Read<uint8_t>() };

				LOGFLN("CP - channel:{}, cpValue:{}", channel, cpValue);
			}
			else if (0xE0 <= status && status <= 0xEF)
			{  // ピッチベンドチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xE0) };
				uint8_t leftSide{ br.Read<uint8_t>() };
				uint8_t rightSide{ br.Read<uint8_t>() };
				uint16_t value{ static_cast<uint16_t>(static_cast<uint16_t>(rightSide) << 7 | leftSide) };

				LOGFLN("Pitch bend - channel:{}, LSB:{:x}, MSB:{:x}", channel, leftSide, rightSide);
			}
			else if (0xA0 <= status && status <= 0xAF)
			{  // キープレッシャー
				uint8_t channel{ static_cast<uint8_t>(status - 0xA0) };
				uint8_t note{ br.Read<uint8_t>() };
				uint8_t press{ br.Read<uint8_t>() };

				LOGFLN("Key pressher - channel:{}, note:{}, press:{}", channel, note, press);
			}
			else if (0x80 <= status && status <= 0x8F)
			{  // ノートオフ
				uint8_t channel{ static_cast<uint8_t>(status - 0x80) };  // チャンネル
				uint8_t note{ br.Read<uint8_t>() };  // 音の高さ
				uint8_t velocity{ br.Read<uint8_t>() };  // 音の強さ
				
				LOGFLN("note off - channel:{}, note:{}, velo:{}", channel, note, velocity);
			}
			else if (0x90 <= status && status <= 0x9F)
			{  // ノートオン
				uint8_t channel{ static_cast<uint8_t>(status - 0x90) };  // チャンネル
				uint8_t note{ br.Read<uint8_t>() };  // 音の高さ
				uint8_t velocity{ br.Read<uint8_t>() };  // 音の強さ

				if (velocity == 0)
				{
					LOGFLN("note off - channel:{}, note:{}, velo:{}", channel, note, velocity);
				}
				else
				{
					truckGen.On(channel, note, velocity);
					LOGFLN("note on - channel:{}, note:{}, velo:{}", channel, note, velocity);
				}
			}
			else
			{
				wassert(false && "未対応のフォーマット");
			}
		}
		truckId++;
	}
#pragma endregion

	readCurr_.resize(truckCount, 0);

	Audio& audio{ System().Get<Audio>() };
	//hTone_[0] = audio.Load("Sound/maou_se_inst_piano2_1do.mp3");
	hTone_[0] = audio.Load("Sound/猫の鳴き声1.mp3");

	toneSampleRateHz_ = audio.GetFormat(hTone_[0]).nSamplesPerSec;
}

void SMFPlayer::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	Audio& audio{ System().Get<Audio>() };

	playTime_ += dt * 1.0f;

	for (int truckId = 0; truckId < smfTrucks_.size(); truckId++)
	{
		if (readCurr_[truckId] >= smfTrucks_[truckId].notes.size())
		{
			continue;
		}
		while (playTime_ >= smfTrucks_[truckId].notes.at(readCurr_[truckId]).totalTime)
		{
			const Note& note{ smfTrucks_[truckId].notes.at(readCurr_[truckId]) };
			readCurr_[truckId]++;

			onNoteCallback_(note);

			LOGFLN("on:{} channel:{}", static_cast<int>(note.noteNumber), note.channel);

			PlayTone(note);

			if (readCurr_[truckId] >= smfTrucks_[truckId].notes.size())
			{
				break;
			}
		}
	}
}

void SMFPlayer::Release()
{
}

uint64_t SMFPlayer::ReadDelta(mtbin::BinaryReader& _br)
{
	uint64_t value = 0;
	uint8_t currentByte;

	do {
		currentByte = _br.Read<uint8_t>();

		// 組み立て中の値(value)を7ビット左にシフトする
		value <<= 7;

		// 読み取ったバイトの下位7ビットを論理和で追加する
		value |= (currentByte & 0x7F);

	} while (currentByte & 0x80); // MSB(0x80)が立っている間はループを続ける

	return value;
	
	//std::array<int8_t, sizeof(uint64_t)> buff{};

	//char miniBuff{};
	//miniBuff = _br.Read<char>();
	//int index{ 0 };

	//buff[index] = miniBuff & 0b0111'1111;
	//index++;

	//while (miniBuff < 0)
	//{  // 最上位ビットが立っているから次も拾う
	//	miniBuff = _br.Read<char>();
	//	buff[index] = miniBuff & 0b0111'1111;
	//	
	//	index++;
	//}

	////std::reverse(buff.begin(), buff.end());

	//return *(reinterpret_cast<uint64_t*>(buff.data()));
}

void SMFPlayer::PlayTone(const Note& _note)
{
	Audio& audio{ System().Get<Audio>() };

	size_t toneHzIndex{ _note.noteNumber - C4_60_NUM + C4_60_INDEX };

	if (toneHzIndex < 0 || HZ.size() <= toneHzIndex)
	{
		return;
	}

	float targetHz{ HZ[toneHzIndex] };

	float sourceHz{ HZ[C4_60_INDEX] };

	float ratio{ targetHz / sourceHz };

	float sampleRate{ static_cast<float>(toneSampleRateHz_) * ratio };

	if (sampleRate <= 192000.0f)
	{
		audio.Play(hTone_[0], _note.playTime, sampleRate);
	}
}

void SMFPlayer::TruckGenerater::SetName(const std::string& _name)
{
	truck_.name = _name;
}

void SMFPlayer::TruckGenerater::SetTempo(const uint32_t _value)
{
	const float MICRO_TO_SEC{ 0.000001f };
	quarterSec_ = static_cast<float>(_value) * MICRO_TO_SEC;
}

void SMFPlayer::TruckGenerater::On(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity)
{
	truck_.notes.push_back(
		{
			currentTime_,
			_channel,
			_note,
			_velocity
		});
}

void SMFPlayer::TruckGenerater::Off(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity)
{
	
}

void SMFPlayer::TruckGenerater::AddDeltaTime(const uint64_t _dt)
{
	if (_dt == 0)
	{
		return;  // デルタタイムが 0 なら無視
	}
	wassert(quarterSec_ != 0);
	float dtSec{ static_cast<float>(_dt) / static_cast<float>(HEADER_.quaterUnit) * quarterSec_ };
	// デルタタイムを秒数で加算する
	currentTime_ += dtSec;
}

float SMFPlayer::TruckGenerater::quarterSec_{ 0.0f };
