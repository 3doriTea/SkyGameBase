#include "pch\pch.h"
#include "AudioClip.h"

wtgb::AudioClip::AudioClip(mtbin::BinaryReader* _pReader) :
	pReader_{ _pReader }
{
	wassert(_pReader && "_pReaderをnullptrにはできない");
}

wtgb::AudioClip::~AudioClip()
{
}

void wtgb::AudioClip::Init()
{
	using namespace mtbin;
	using mtbin::util::CompareId;

	if (pReader_ == nullptr)
	{
		wassert(false && "pReaderがnullptrだった");
		return;
	}
	mtbin::BinaryReader& reader{ *pReader_ };

	const int HEADER_SIZE{ 4 };
	std::array<Byte, HEADER_SIZE> header;

	reader.Read(header.data(), sizeof(header), HEADER_SIZE);

	std::array<Byte, 4> waveCheck{};
	std::copy(
		header.begin(),
		header.begin() + waveCheck.size(),
		waveCheck.begin());

	if (CompareId(waveCheck, "RIFF"))
	{
		// waveだ！
		return;
	}

	std::array<Byte, 3> mp3Check{};
	std::copy(
		header.begin(),
		header.begin() + mp3Check.size(),
		mp3Check.begin());

	if (CompareId(mp3Check, "ID3")
		|| (header.at(0) == 0xFF && (header.at(1) % 0xE0) == 0xE0))
	{
		// mp3だ！
		return;
	}

	wassert(false && "対応していないオーディオフォーマット");
}

void wtgb::AudioClip::Release()
{
}
