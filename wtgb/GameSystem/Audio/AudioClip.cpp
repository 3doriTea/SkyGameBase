#include "pch\pch.h"
#include "AudioClip.h"
//#include "GameSystem/Audio/DrLibsInclude.h"

#ifndef DR_MP3_IMPLEMENTATION

#define DR_MP3_IMPLEMENTATION 1
#include "Library/dr_libs/dr_mp3.h"

#endif


wtgb::AudioClip::AudioClip(mtbin::BinaryReader* _pReader, const std::string& _name) :
	pReader_{ _pReader },
	name_{ _name }
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

	if (std::array<Byte, 4> waveCheck{ header };
		CompareId(waveCheck, "RIFF"))
	{
		wassert(false && "TODO: 未実装のwave読み込み");
		// waveだ！
	}
	else if (  // TODO: だいぶひどい
		std::array<Byte, 3> mp3Check{ header.at(0), header.at(1), header.at(2) };
		CompareId(mp3Check, "ID3")
		|| (header.at(0) == 0xFF && (header.at(1) & 0b1110'0000) == 0b1110'0000))
	{
		// mp3だ！
		LoadMp3();
	}
	else  // 未対応のフォーマット
	{
		wassert(false && "対応していないオーディオフォーマット");
	}

	pReader_ = nullptr;  // 読み込み終わって使わないためnullptr
}

void wtgb::AudioClip::Release()
{
	buffer_.clear();  // 念の為
}

float wtgb::AudioClip::GetTotalTimeSec() const
{
	wassert(waveFormat_.nAvgBytesPerSec != 0 && "0除算発生");
	return buffer_.size() / static_cast<float>(waveFormat_.nAvgBytesPerSec);
}

void wtgb::AudioClip::LoadMp3()
{
	using namespace mtbin;

	BinaryReader& reader{ *pReader_ };
	reader.Seek(SeekAt::Head);

	size_t size{ reader.Size() };

	// drmp3の変換準備
	drmp3 config{};
	drmp3_bool32 succeed{ drmp3_init_memory(&config, reader.Data(), reader.Size(), nullptr) };
	wassert(succeed && "mp3読み込み準備に失敗");
	if (succeed == false)
	{
		return;
	}
	
	// PCMサンプル数の取得
	drmp3_uint64 totalSamples{ drmp3_get_pcm_frame_count(&config) };

	// バッファサイズの計算
	size_t pcmSampleCount{ static_cast<size_t>(totalSamples * config.channels) };
	size_t pcmBytes{ pcmSampleCount * sizeof(drmp3_int16) };

	// バッファの準備
	buffer_.clear();
	buffer_.resize(pcmBytes);

	// いざ読み込む
	drmp3_read_pcm_frames_s16(&config, totalSamples, reinterpret_cast<drmp3_int16*>(buffer_.data()));

	const WORD CHANNELS{ static_cast<WORD>(config.channels) };
	const DWORD BITS_PER_SAMPLE{ 16 };
	const WORD BLOCK_ALIGN{ static_cast<WORD>(CHANNELS * BITS_PER_SAMPLE / 8) };
	const DWORD SAMPLE_RATE{ static_cast<DWORD>(config.sampleRate) };

	// waveフォーマット情報の設定
	waveFormat_ = WAVEFORMATEX
	{
		.wFormatTag = 1,
		.nChannels = CHANNELS,
		.nSamplesPerSec = SAMPLE_RATE,
		.nAvgBytesPerSec = SAMPLE_RATE * BLOCK_ALIGN,
		.nBlockAlign = BLOCK_ALIGN,
		.wBitsPerSample = BITS_PER_SAMPLE,
	};

	// 後片付け
	drmp3_uninit(&config); 
}
