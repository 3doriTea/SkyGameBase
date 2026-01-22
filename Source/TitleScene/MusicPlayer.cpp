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
	
}

void MusicPlayer::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	// smf ÉvÉåÉCÉÑÅ[ÇìoèÍÇ≥ÇπÇÈ
	EntityId smfPlayer
	{
		GetScene<TitleScene>().Instantiate<SMFPlayer>(smfPath_)
	};

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer)) };
	pSMFPlayer->Play();
}

void MusicPlayer::Update()
{
}

void MusicPlayer::Release()
{
}

