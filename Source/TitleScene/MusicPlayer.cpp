#include "MusicPlayer.h"
#include "SMF/SMFPlayer.h"
#include "TitleScene.h"

MusicPlayer::MusicPlayer() :
	GameObject{ "MusicPlayer.json" }
{
}

MusicPlayer::~MusicPlayer()
{
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

	// smf プレイヤーを登場させる
	EntityId smfPlayer
	{
		GetScene<TitleScene>().Instantiate<SMFPlayer>(smfPath_)
	};
	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer)) };

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

