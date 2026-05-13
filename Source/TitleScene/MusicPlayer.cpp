#include "MusicPlayer.h"
#include "SMF/SMFPlayer.h"
#include "TitleScene.h"

MusicPlayer::MusicPlayer() :
	GameObject{ "MusicPlayer.json" },
	smfPlayer_{ INVALID_ENTITY },
	smfPath_{},
	toneAudioFilePath_{}
{
}

MusicPlayer::~MusicPlayer()
{
}

void MusicPlayer::StopAndClear()
{
	Stop();
	// 再生中の音をクリア
	System().Get<Audio>().ClearAll();
}

void MusicPlayer::Stop()
{
	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	wassert(pSMFPlayer && "SMFPlayerが見つからなかった");
	if (pSMFPlayer == nullptr)
	{
		return;  // SMFPlayerの取得に失敗すると何もできない
	}

	// 再生停止
	pSMFPlayer->Stop();
}

void MusicPlayer::OnLoadParam(const json& _json)
{
	smfPath_ = SafeGet<std::string>(_json, "smfPath");
	toneAudioFilePath_ = SafeGet<std::string>(_json, "toneAudioFilePath");
}

void MusicPlayer::Init()
{
	Audio& audio{ System().Get<Audio>() };

	OnLoadParam(GetComponent<Parameter>().Load());

	TitleScene* pTitleScene{ GetScene<TitleScene>() };
	wassert(pTitleScene && "タイトルシーンの取得に失敗");
	if (pTitleScene == nullptr)
	{
		return;  // タイトルシーンの取得に失敗すると何もできない
	}

	// smf プレイヤーを登場させる
	smfPlayer_ = pTitleScene->Instantiate<SMFPlayer>(smfPath_);
	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	wassert(pSMFPlayer && "インスタンスしたはずのSMFPlayerが見つからなかった");
	if (pSMFPlayer == nullptr)
	{
		return;  // SMFPlayerの取得に失敗すると何もできない
	}


	// ノーツ再生時の音源読み込み && セット
	pSMFPlayer->SetToneAudioHandle(
		audio.Load(toneAudioFilePath_));

	// ノーツの処理を登録
	pSMFPlayer->OnNote([this, pSMFPlayer](Note _note)
		{
			if (_note.channel == 0x03)
			{
				pSMFPlayer->PlayTone(_note);
			}
		});

	// 再生！
	pSMFPlayer->Play();
}

void MusicPlayer::Update()
{
}

void MusicPlayer::Release()
{
}

