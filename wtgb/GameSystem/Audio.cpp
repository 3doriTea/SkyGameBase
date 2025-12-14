#include "pch\pch.h"
#include "Audio.h"
#include "WTGBAssert.h"
#include "GameTime.h"

wtgb::Audio::Audio() :
	audioPlayer_{},
	pMasteringVoice_{}
{
}

wtgb::Audio::~Audio()
{
}

wtgb::Result wtgb::Audio::Init(const ViewerInit& _viewer)
{
	HRESULT hResult{};

	hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	wassert(SUCCEEDED(hResult) && "COMの初期化に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	hResult = XAudio2Create(pXAudio2_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "COMの初期化に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	IXAudio2MasteringVoice* pMasteringVoice{ nullptr };
	hResult = pXAudio2_.Get()->CreateMasteringVoice(&pMasteringVoice);
	//hResult = pXAudio2_.Get()->CreateMasteringVoice(pMasteringVoice_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "主音声の作成に失敗");
	if (FAILED(hResult))
	{
		return Result::Code::Failed;
	}

	pMasteringVoice_.reset(pMasteringVoice);

	return Result::Code::Ok;
}

void wtgb::Audio::Update(const ViewerUpdate& _system)
{
	const float dt{ _system.Get<GameTime>().GetDeltaTime() };
	audioPlayer_.Update(dt);  // 更新する
}

void wtgb::Audio::End()
{
	audioPlayer_.Clear();
}

void wtgb::Audio::CreateSourceVoice(IXAudio2SourceVoice** _ppSourceVoice, const WAVEFORMATEX& _format)
{
	HRESULT hResult{};
	hResult = pXAudio2_.Get()->CreateSourceVoice(_ppSourceVoice, &_format);
	wassert(SUCCEEDED(hResult) && "SourceVoiceの作成に失敗");
}

wtgb::AudioHandle wtgb::Audio::Load(const fs::path& _audioFileName)
{
	AudioHandle foundHandle
	{
		audioClips_.GetContainsDuplicate([&_audioFileName](AudioClip& _clip) -> bool
			{
				return _clip.GetName() == _audioFileName;
			})
	};

	if (foundHandle != INVALID_HANDLE)
	{
		// 既に読み込まれた音声ならそのハンドルを返す
		return foundHandle;
	}

	//  REF: https://learn.microsoft.com/ja-jp/windows/win32/api/fileapi/nf-fileapi-createfilea
	HANDLE hFile = CreateFile(
		_audioFileName.string().c_str(),  // ファイル名
		GENERIC_READ,                     // 読み取りますよー
		FILE_SHARE_READ,                  // Closeされるまで、他のアプリはファイルの読み取りだけしていいよー
		nullptr,                          // セキュリティ属性用の構造体ポインタを指定
		OPEN_EXISTING,                    // 開く - ファイルが無かったら失敗
		FILE_ATTRIBUTE_NORMAL,            // 普通のファイル属性
		NULL);                            // 既存のファイルを開く場合は関係ないやつ

	if (hFile == INVALID_HANDLE_VALUE)
	{
		wassert(false && "ファイルOpenに失敗");
		return INVALID_HANDLE;
	}

	BOOL succeed{ FALSE };

	//  REF: https://learn.microsoft.com/ja-jp/windows/win32/api/fileapi/nf-fileapi-getfilesizeex
	LARGE_INTEGER fileSize{};  // ファイルサイズ格納用
	succeed = GetFileSizeEx(hFile, &fileSize);
	if (succeed == FALSE)
	{
		wassert(false && "ファイルサイズ取得に失敗");
		return INVALID_HANDLE;
	}

	DWORD readedSize{ 0 };  // 実際に読み取れたバイト数

	std::vector<byte> buffer(fileSize.QuadPart, 0x00);

	succeed = ReadFile(
		hFile,
		buffer.data(),
		static_cast<DWORD>(fileSize.QuadPart),
		&readedSize,
		nullptr);

	if (succeed == FALSE || readedSize != fileSize.QuadPart)
	{
		wassert(false && "ファイルの読み取りに失敗");
		return INVALID_HANDLE;
	}

	CloseHandle(hFile);  // ファイルを閉じる


	mtbin::BinaryReader br{ buffer.data(), buffer.size() };

	AudioHandle hAudio{ audioClips_.Emplace(&br, _audioFileName.string()) };
	audioClips_.At(hAudio).CallInit();  // 初期化 = 読み取ってもらう

	return hAudio;
}

void wtgb::Audio::Play(const AudioHandle _hAudio)
{
	const AudioClip& clip{ audioClips_.At(_hAudio) };

	const XAUDIO2_BUFFER BUFFER
	{
		.Flags = XAUDIO2_END_OF_STREAM,
		.AudioBytes = static_cast<UINT32>(clip.GetBufferSize()),
		.pAudioData = reinterpret_cast<const BYTE*>(clip.GetBufferData()),
		.LoopCount = 0,
	};

	SourceVoiceIndex index = audioPlayer_.Play(BUFFER, clip.GetFormat(), *this);
	wassert(index >= 0 && "再生に失敗");
}
