#include "pch\pch.h"
#include "DropCloud.h"
#include "Player.h"
#include "StageLine.h"
#include "SMF/SMFPlayer.h"

namespace
{
	// 地上からの高さ デフォルト
	static const float HEIGHT{ 100.0f };
}

DropCloud::DropCloud(
	const EntityId _smfPlayer,
	const EntityId _gamePlayer,
	const EntityId _stageLine) :
	GameObject{ "DropCloud" },
	smfPlayer_{ _smfPlayer },
	player_{ _gamePlayer },
	stageLine_{ _stageLine },
	offsetHeight_{ HEIGHT }
{
}

DropCloud::~DropCloud()
{
}

void DropCloud::Init()
{
	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer_)) };
	if (pSMFPlayer)
	{
		Audio& audio{ System().Get<Audio>() };

		// ノーツ再生時の音源読み込み && セット
		pSMFPlayer->SetToneAudioHandle(
			audio.Load("Sound/385892__spacether__262312__steffcaffrey__cat-meow1.mp3"));

		// ノーツの処理を登録
		pSMFPlayer->OnNote([pSMFPlayer](Note _note)
			{
				if (_note.channel == 0x03)
				{
					

					_note.noteNumber -= 12 * 2;
					pSMFPlayer->PlayTone(_note);
				}
			});


		// 再生！
		pSMFPlayer->Play();
	}
}

void DropCloud::Update()
{
	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer_)) };
	Player* pPlayer{ dynamic_cast<Player*>(FindGameObject(player_)) };
	StageLine* pStageLine{ dynamic_cast<StageLine*>(FindGameObject(stageLine_)) };

	Vector3 position{ Transform().GetPosition() };
	position.y = pStageLine->GetPosY(position) + offsetHeight_;
	Transform().SetPosition(position);


}

void DropCloud::Release()
{
}
