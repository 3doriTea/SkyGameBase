#include "pch/pch.h"
#include "SMFPlayer.h"
#include "ToneHz.h"

//#define USE_SMF_PLAYER_LOG

using namespace SMF;

SMFPlayer::SMFPlayer(const fs::path& _file) :
	GameObject{ "SMFPlayer.json" },
	file_{ _file },
	readCurr_{},
	hTone_{ INVALID_HANDLE },
	playTime_{},
	toneSampleRateHz_{},
	onNoteCallback_{ [](const Note&){} },
	playRate_{ 1.0f },
	isPlaying_{ false }
{
}

SMFPlayer::~SMFPlayer()
{
}

void SMFPlayer::OnNote(const std::function<void(Note)> _callback)
{
	onNoteCallback_ = _callback;
}

void SMFPlayer::Init()
{
	using namespace mtbin;
	using mtbin::util::CompareId;
	using mtbin::util::Reverse;

	OnLoadParam(GetComponent<Parameter>().Load());

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
	uint16_t format{ br.ReadRev<uint16_t>() };
	uint16_t truckCount{ br.ReadRev<uint16_t>() };

#ifdef USE_SMF_PLAYER_LOG
	LOGFLN("HeaderSize:{}", headerSize);
	LOGFLN("Format:{}", format);
	LOGFLN("truckCount:{}", truckCount);
#endif

	smfTrucks_.resize(truckCount);

	int16_t timeUnit{ br.ReadRev<int16_t>() };
	if (timeUnit < 0)
	{
		wassert("分解能が何分何秒何フレームは対応していないよ");
	}
	smfHeader_.quarterUnit = timeUnit;
#ifdef USE_SMF_PLAYER_LOG
	LOGFLN("timeUnit:{}", timeUnit);
#endif
#pragma endregion

#pragma region トラックチャンク
	int truckId{ 0 };
	while (br.Current() < br.Size())
	{
#ifdef USE_SMF_PLAYER_LOG
		LOGFLN("--------------------truckCount:{} / {}--------------------", truckId, truckCount);
#endif
		if (br.Read(buff4.data(), 4, 4); !CompareId(buff4, "MTrk"))
		{
			wassert(false && "トラックヘッダ不一致");
			return;
		}

		uint32_t headerSize{ br.ReadRev<uint32_t>() };
#ifdef USE_SMF_PLAYER_LOG
		LOGFLN("HeaderSize:{}", headerSize);
#endif
		uint8_t prevStatus{};  // ランニングステータス用
		size_t endOfTruckPos{ br.Current() + headerSize };

		TruckGenerator truckGen{ smfTrucks_.at(truckId), smfHeader_, channelToToneMinMax_ };

		bool endOfTruckFlag{ false };
		while (br.Current() < endOfTruckPos && !endOfTruckFlag)
		{
			uint64_t delta{ ReadDelta(br) };
			truckGen.AddDeltaTime(delta);
#ifdef USE_SMF_PLAYER_LOG
			LOGFLN("DeltaTime:{}", delta);
#endif

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
#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("StatusR:{:x}", +status);
#endif
			}
			else
			{
				status = br.Read<uint8_t>();
#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("Status:{:x}", +status);
#endif
			}

			if (status != 0xF0 && status != 0xF7)
			{
				prevStatus = status;  // SystemEx以外はランニングに使える
			}

			if (status == 0xFF)
			{  // メタイベント
				uint8_t subStatus{ br.Read<uint8_t>() };
#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("meta");
#endif
				switch (subStatus)
				{
				case 0x00:  // シーケンス番号
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint16_t sequenceNumber{ br.ReadRev<uint16_t>() };
#ifdef USE_SMF_PLAYER_LOG
					LOGFLN("Sequence:{} size:{}", sequenceNumber, size);
#endif
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

					break;
				}
				case 0x20:  // MIDIチャンネルプレフィックス
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint8_t channel{ br.Read<uint8_t>() };
					
					//LOGFLN("channel prefix channel{} size{}", channel, size);
					break;
				}
				case 0x21:  // MIDIポートプレフィックス
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint8_t port{ br.Read<uint8_t>() };  // ポート番号

					//LOGFLN("port prefix port{} size{}", port, size);
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
					quarterSec_ = truckGen.GetQuarterSec();
					break;
				}
				default:
				{
					int size{ static_cast<int>(ReadDelta(br)) };
					std::vector<char> textBuffer(size, '\0');

					br.Read(textBuffer.data(), size, size);
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
#ifdef USE_SMF_PLAYER_LOG
						LOGFLN("Skiped 0xF7");
#endif
					}
				}

				std::vector<char> textBuffer(size, '\0');
				br.Read(textBuffer.data(), size, size);
#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("SystemEx size:{}", size);
#endif
			}
			else if (0xB0 <= status && status <= 0xBF)
			{  // コントロールチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xB0) };
				uint8_t ccNum{ br.Read<uint8_t>() };
				uint8_t ccValue{ br.Read<uint8_t>() };

#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("CC - channel:{}, number:{}, value:{}", channel, ccNum, ccValue);
#endif
			}
			else if (0xC0 <= status && status <= 0xCF)
			{  // プログラムチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xC0) };
				uint8_t pcNum{ br.Read<uint8_t>() };

#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("PC - channel:{}, number:{}", channel, pcNum);
#endif
			}
			else if (0xD0 <= status && status <= 0xDF)
			{  // チャンネルプレッシャー / アフタータッチ
				uint8_t channel{ static_cast<uint8_t>(status - 0xD0) };
				uint8_t cpValue{ br.Read<uint8_t>() };

#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("CP - channel:{}, cpValue:{}", channel, cpValue);
#endif
			}
			else if (0xE0 <= status && status <= 0xEF)
			{  // ピッチベンドチェンジ
				uint8_t channel{ static_cast<uint8_t>(status - 0xE0) };
				uint8_t leftSide{ br.Read<uint8_t>() };
				uint8_t rightSide{ br.Read<uint8_t>() };
				uint16_t value{ static_cast<uint16_t>(static_cast<uint16_t>(rightSide) << 7 | leftSide) };

#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("Pitch bend - channel:{}, LSB:{:x}, MSB:{:x}", channel, leftSide, rightSide);
#endif
			}
			else if (0xA0 <= status && status <= 0xAF)
			{  // キープレッシャー
				uint8_t channel{ static_cast<uint8_t>(status - 0xA0) };
				uint8_t note{ br.Read<uint8_t>() };
				uint8_t press{ br.Read<uint8_t>() };

#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("Key pressure - channel:{}, note:{}, press:{}", channel, note, press);
#endif
			}
			else if (0x80 <= status && status <= 0x8F)
			{  // ノートオフ
				uint8_t channel{ static_cast<uint8_t>(status - 0x80) };  // チャンネル
				uint8_t note{ br.Read<uint8_t>() };  // 音の高さ
				uint8_t velocity{ br.Read<uint8_t>() };  // 音の強さ
				
				truckGen.Off(channel, note, velocity);
#ifdef USE_SMF_PLAYER_LOG
				LOGFLN("note off - channel:{}, note:{}, velo:{}", channel, note, velocity);
#endif
			}
			else if (0x90 <= status && status <= 0x9F)
			{  // ノートオン
				uint8_t channel{ static_cast<uint8_t>(status - 0x90) };  // チャンネル
				uint8_t note{ br.Read<uint8_t>() };  // 音の高さ
				uint8_t velocity{ br.Read<uint8_t>() };  // 音の強さ

				if (velocity == 0)
				{
					truckGen.Off(channel, note, velocity);
#ifdef USE_SMF_PLAYER_LOG
					LOGFLN("note off - channel:{}, note:{}, velo:{}", channel, note, velocity);
#endif
				}
				else
				{
					truckGen.On(channel, note, velocity);
#ifdef USE_SMF_PLAYER_LOG
					LOGFLN("note on - channel:{}, note:{}, velo:{}", channel, note, velocity);
#endif
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

#pragma region 曲全体の情報取得
	totalPlayTime_ = 0.0f;
	for (const auto& truck : smfTrucks_)
	{
		if (truck.notes.empty())
		{
			continue;
		}
		const Note& lastNote{ truck.notes.at(truck.notes.size() - 1) };
		const float TOTAL_PLAY_TIME{ lastNote.startTime + lastNote.playTime };

		// 各トラックで最大時間を全探索して見つける
		if (TOTAL_PLAY_TIME > totalPlayTime_)
		{
			totalPlayTime_ = TOTAL_PLAY_TIME;
		}
	}
#pragma endregion

#pragma region 再生データの初期化
	readCurr_.clear();
	readCurr_.resize(truckCount, 0);
#pragma endregion
}

void SMFPlayer::Update()
{
	if (isPlaying_ == false)
	{  // 再生されていないなら回帰
		return;
	}

	float dt{ System().Get<GameTime>().GetDeltaTime() };

	playTime_ += dt * playRate_;

	// 各トラックを周回する
	for (int truckId = 0; truckId < smfTrucks_.size(); truckId++)
	{
		if (readCurr_[truckId] >= smfTrucks_[truckId].notes.size())
		{
			continue;  // このトラックは末端まで読んだため無視
		}

		// 次を待っているノードに再生時間がやってきたか (その次の次もチェックのため while)
		while (playTime_ >= smfTrucks_[truckId].notes.at(readCurr_[truckId]).startTime)
		{
			const Note& note{ smfTrucks_[truckId].notes.at(readCurr_[truckId]) };
			readCurr_[truckId]++;

			// コールバックを呼び出す
			onNoteCallback_(note);

			if (readCurr_[truckId] >= smfTrucks_[truckId].notes.size())
			{
				break;  // トラックの末端まで読んだ
			}
		}
	}
}

void SMFPlayer::Release()
{
}

uint64_t SMFPlayer::ReadDelta(mtbin::BinaryReader& _br)
{
	uint64_t value{ 0 };
	uint8_t currentByte{};

	while (true)
	{
		currentByte = _br.Read<uint8_t>();
		// 組み立て中の値(value)を7ビット左にシフトする
		value <<= 7;
		// 読み取ったバイトの下位7ビットを合体
		value |= (currentByte & 0x7F);

		if (currentByte & 0x80)
		{
			// MSB(0x80)が立っている間はループを続ける
			continue;
		}
		else
		{
			break;
		}
	}
	return value;
}

void SMFPlayer::PlayTone(const Note& _note)
{
	PlayTone(_note, hTone_, C4_60_INDEX);
}
void SMFPlayer::PlayTone(const Note& _note, const AudioHandle _hTone, const int32_t _offset)
{
	if (_hTone == INVALID_HANDLE)
	{
		return;  // 無効ハンドルなら再生しない
	}
	SetToneAudioHandle(_hTone);

	Audio& audio{ System().Get<Audio>() };

	size_t toneHzIndex{ static_cast<size_t>(_note.noteNumber - C4_60_NUM + _offset) };

	if (toneHzIndex < 0 || TONE_HZ.size() <= toneHzIndex)
	{
		return;
	}

	float targetHz{ TONE_HZ[toneHzIndex] };

	float sourceHz{ TONE_HZ[C4_60_INDEX] };

	float ratio{ targetHz / sourceHz };

	float sampleRate{ static_cast<float>(toneSampleRateHz_) * ratio };

	// リミット以下なら再生
	if (sampleRate <= playableSampleRateLimit_)
	{
		audio.Play(_hTone, _note.playTime, static_cast<unsigned long>(sampleRate));
	}
}

void SMFPlayer::SetToneAudioHandle(const AudioHandle _hAudio)
{
	Audio& audio{ System().Get<Audio>() };

	hTone_ = _hAudio;  // 音源ハンドル指定しつつ
	// サンプルレートも更新する
	toneSampleRateHz_ = static_cast<float>(audio.GetFormat(_hAudio).nSamplesPerSec);
}

void SMFPlayer::OnLoadParam(const json& _json)
{
	playableSampleRateLimit_ = SafeGet<float>(_json, "playableSampleRateLimit");
}

void SMFPlayer::TruckGenerator::SetName(const std::string& _name)
{
	truck_.name = _name;
}

void SMFPlayer::TruckGenerator::SetTempo(const uint32_t _value)
{
	const float MICRO_TO_SEC{ 0.000001f };
	quarterSec_ = static_cast<float>(_value) * MICRO_TO_SEC;
}

void SMFPlayer::TruckGenerator::On(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity)
{
	if (_note > truck_.toneMax)
	{
		// 最大トーン更新
		truck_.toneMax = _note;
	}
	if (_note < truck_.toneMin)
	{
		// 最小トーン更新
		truck_.toneMin = _note;
	}

	if (!channelToToneMinMax_.contains(_channel))
	{
		// チャンネルが含まれていないなら追加
		channelToToneMinMax_.insert({ _channel, { UINT8_MAX, 0x00 } });
	}

	auto& [toneMin, toneMax]{ channelToToneMinMax_[_channel] };
	if (_note > toneMax)
	{
		// 最大トーン更新
		toneMax = _note;
	}
	if (_note < toneMin)
	{
		// 最小トーン更新
		toneMin = _note;
	}

#ifdef USE_SMF_PLAYER_LOG
	LOGFLN("currentTime={}", currentTime_);
#endif
	truck_.notes.push_back(
		{
			currentTime_,
			_channel,
			_note,
			_velocity
		});
}

void SMFPlayer::TruckGenerator::Off(const uint8_t _channel, const uint8_t _note, const uint8_t _velocity)
{
	// 同じチャンネルの同じトーンのノーツを探す
	for (auto itr = truck_.notes.rbegin(); itr != truck_.notes.rend(); itr++)
	{
		if (itr->channel == _channel && itr->noteNumber == _note)
		{  // 見つかった
			itr->playTime = currentTime_ - itr->startTime;
			return;  // 時間指定して回帰
		}
	}
}

void SMFPlayer::TruckGenerator::AddDeltaTime(const uint64_t _dt)
{
	if (_dt == 0)
	{
		return;  // デルタタイムが 0 なら無視
	}
	wassert(quarterSec_ != 0);
	float dtSec{ static_cast<float>(_dt) / static_cast<float>(HEADER_.quarterUnit) * quarterSec_ };
	// デルタタイムを秒数で加算する
	currentTime_ += dtSec;
}

float SMFPlayer::TruckGenerator::quarterSec_{ 0.0f };
