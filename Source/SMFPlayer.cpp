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


		while (true)
		{
			uint64_t delta{ ReadDelta(br) };
			LOGFLN("DeltaTime:{}", delta);

			uint8_t event{ br.Read<uint8_t>() };
			LOGFLN("Event:{}", event);


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
	char miniBuff{};

	miniBuff = _br.Read<char>();

	uint64_t value{};
	while (miniBuff < 0)
	{
		value <<= 7;
		value |= miniBuff & 0b0111'1111;
	}

	std::array<uint8_t, sizeof(value)> bytes{};
	for (int i = 0; i < sizeof(value); i++)
	{
		uint8_t* p{ reinterpret_cast<uint8_t*>(&value) };
		bytes[i] = *p;
	}
	std::reverse(bytes.begin(), bytes.end());

	value = *reinterpret_cast<uint64_t*>(bytes.data());
	return value;
}
