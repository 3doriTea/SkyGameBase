#include "pch/pch.h"
#include "SMFPlayer.h"
#include <bit>

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
	file_{ _file }
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

	std::ifstream smf{ file_ };

	if (!smf)
	{
		wassert(false && "ファイル読み込み失敗");
		return;
	}

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
	LOGFLN("HeaderSize:{}", headerSize);

	uint16_t format{ br.ReadRev<uint16_t>() };
	LOGFLN("Format:{}", format);

	uint16_t truckCount{ br.ReadRev<uint16_t>() };
	LOGFLN("truckCount:{}", truckCount);

	int16_t timeUnit{ br.ReadRev<int16_t>() };
	if (timeUnit < 0)
	{
		wassert("分解能が何分何秒何フレームは対応していないよ");
	}
	LOGFLN("timeUnit:{}", timeUnit);
#pragma endregion

#pragma region トラックチャンク
	int truckId{ 0 };
	while (br.Current() < br.Size())
	{
		truckId++;
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

		bool endOfTruckFlag{ false };
		while (br.Current() < endOfTruckPos && !endOfTruckFlag)
		{
			uint64_t delta{ ReadDelta(br) };
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
					uint64_t size{ ReadDelta(br) };
					std::vector<char> textBuffer(size, '\0');
					br.Read(textBuffer.data(), size, size);

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
					std::array<Byte, 4> paste{ buff[2], buff[1], buff[0], 0x00 };
					uint32_t tempo
					{
						(static_cast<uint32_t>(buff[0]) << 16) |
						(static_cast<uint32_t>(buff[1]) << 8) |
						(static_cast<uint32_t>(buff[2]) << 0)
					};

					LOGFLN("set tempo:{}", tempo);
					break;
				}
				default:
				{
					uint64_t size{ ReadDelta(br) };
					std::vector<char> textBuffer(size, '\0');

					br.Read(textBuffer.data(), size, size);
					LOGFLN("???{:x}:{}", subStatus, textBuffer.data());
					break;
				}
				}
			}
			else if (status == 0xF0 || status == 0xF7)
			{  // システム拡張イベント
				uint64_t size{ ReadDelta(br) };

				if (status == 0xF0)
				{
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
					LOGFLN("note on - channel:{}, note:{}, velo:{}", channel, note, velocity);
				}
			}
			else
			{
				wassert(false && "未対応のフォーマット");
			}
		}
	}
#pragma endregion
}

void SMFPlayer::Update()
{
}

void SMFPlayer::Release()
{
}

uint64_t SMFPlayer::ReadDelta(mtbin::BinaryReader& _br)
{
	std::array<int8_t, sizeof(uint64_t)> buff{};

	char miniBuff{};
	miniBuff = _br.Read<char>();
	int index{ 0 };

	buff[index] = miniBuff & 0b0111'1111;
	index++;

	while (miniBuff < 0)
	{  // 最上位ビットが立っているから次も拾う
		miniBuff = _br.Read<char>();
		buff[index] = miniBuff & 0b0111'1111;
		
		index++;
	}

	//std::reverse(buff.begin(), buff.end());

	return *(reinterpret_cast<uint64_t*>(buff.data()));

	//while (miniBuff < 0)
	//{
	//	value <<= 7;
	//	value |= miniBuff & 0b0111'1111;
	//}
	//value <<= 7;
	//value |= miniBuff & 0b0111'1111;

	//std::array<uint8_t, sizeof(value)> bytes{};
	//for (int i = 0; i < sizeof(value); i++)
	//{
	//	uint8_t* p{ reinterpret_cast<uint8_t*>(&value) };
	//	bytes[i] = *p;
	//}
	//std::reverse(bytes.begin(), bytes.end());

	//value = *reinterpret_cast<uint64_t*>(bytes.data());
	//return value;
}
