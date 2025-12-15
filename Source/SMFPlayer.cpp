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

		bool endOfTruckFlag{ false };
		while (!endOfTruckFlag)
		{
			uint64_t delta{ ReadDelta(br) };
			LOGFLN("DeltaTime:{}", delta);

			uint8_t status{ br.Read<uint8_t>() };
			LOGFLN("Status:{:x}", +status);

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
					uint8_t port{ br.Read<uint8_t>() };
					
					LOGFLN("channel prefix port{} size{}", port, size);
					break;
				}
				case 0x21:  // MIDIポートプレフィックス
				{
					uint8_t size{ br.Read<uint8_t>() };
					uint8_t port{ br.Read<uint8_t>() };

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
					uint32_t tempo = *(reinterpret_cast<uint32_t*>(paste.data()));

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
				LOGFLN("SystemEx size:{}");
			}
			else if (0xA0 <= status && status <= 0xEF)
			{  // コントロールチェンジ
				uint8_t unknown[3]{};
				unknown[0] = br.Read<uint8_t>();
				unknown[1] = br.Read<uint8_t>();
				unknown[2] = br.Read<uint8_t>();

				wassert(false && "システム拡張は対応していない");
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

				LOGFLN("note on - channel:{}, note:{}, velo:{}", channel, note, velocity);
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
