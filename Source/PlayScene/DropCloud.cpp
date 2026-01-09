#include "pch\pch.h"
#include "DropCloud.h"
#include "Player.h"
#include "StageLine.h"
#include "SMF/SMFPlayer.h"
#include "PlayScene.h"
#include "PresentSphere.h"

namespace
{
	// 地上からの高さ デフォルト
	static const float HEIGHT{ 100.0f };
	static const float DESTORY_DISTANCE_Z{ 300.0f };
	static const int PLAY_NOTE_NUMBER_OFFSET{ 12 * 2 };  // 再生する音のオフセット
}

DropCloud::DropCloud(
	const EntityId _smfPlayer,
	const EntityId _gamePlayer,
	const EntityId _stageLine) :
	GameObject{ "DropCloud.json" },
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
		StageLine* pStageLine{ dynamic_cast<StageLine*>(FindGameObject(stageLine_)) };
		wassert(pStageLine && "ステージラインがシーンに存在しないよ！");

		// ノーツ再生時の音源読み込み && セット
		pSMFPlayer->SetToneAudioHandle(
			audio.Load("Sound/385892__spacether__262312__steffcaffrey__cat-meow1.mp3"));

		// ノーツの処理を登録
		pSMFPlayer->OnNote([this, pSMFPlayer, pStageLine](Note _note)
			{
				if (_note.channel == 0x03)
				{
					dropedPresents_.push_back(DropedPresent
						{
							.entityId = GetScene<PlayScene>().Instantiate<PresentSphere>(
								player_,
								Transform().GetPosition(),
								Vector3{ Transform().GetPosition().x, pStageLine->GetPosY(Transform().GetPosition()), Transform().GetPosition().z }),
							.note = _note,
						});
				}
			});


		// 再生！
		pSMFPlayer->Play();
	}
}

void DropCloud::Update()
{
	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject(smfPlayer_)) };
	Player* pPlayer{ dynamic_cast<Player*>(FindGameObject(player_)) };
	StageLine* pStageLine{ dynamic_cast<StageLine*>(FindGameObject(stageLine_)) };

	Vector3 position{ pPlayer->Transform().GetPosition() };
	position.z += 100.0f;
	position.y = pStageLine->GetPosY(position) + offsetHeight_;
	Transform().SetPosition(position);

	for (auto itr = dropedPresents_.begin(); itr != dropedPresents_.end();)
	{
		GameObject* pPresentObj{ FindGameObject(itr->entityId) };
		PresentSphere* pPresent{ dynamic_cast<PresentSphere*>(FindGameObject(itr->entityId)) };

		if ((position.z - pPresent->Transform().GetPosition().z) > DESTORY_DISTANCE_Z)
		{
			pPresent->DestroyMe();
			itr = dropedPresents_.erase(itr);
			continue;
		}

		if (pPresent->IsHit())
		{
			pPresent->DestroyMe();
			itr = dropedPresents_.erase(itr);
			continue;
		}
		if (pPresent->CheckOnBounded())
		{
			itr->note.noteNumber -= PLAY_NOTE_NUMBER_OFFSET;
			pSMFPlayer->PlayTone(itr->note);
		}

		itr++;
	}
}

void DropCloud::Release()
{
}
