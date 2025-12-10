#include "pch/pch.h"
#include "StageObjectManager.h"
#include "../SampleScene/Player.h"
#include "StageLine.h"
#include "SpecialBall.h"
#include "PlayScene.h"


StageObjectManager::StageObjectManager(const EntityId _stageLine, const EntityId _player) : GameObject
{
	[](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("StageObjectManager")
				.EndSetter()
		.Build();
	}
},
	stageLine_{ _stageLine },
	player_{ _player }
{
}

StageObjectManager::~StageObjectManager()
{
}

void StageObjectManager::Init()
{
}

void StageObjectManager::Update()
{
	GameObject* pStageLineObj{ FindGameObject(stageLine_) };
	StageLine* pStageLine{ dynamic_cast<StageLine*>(pStageLineObj) };
	wassert(pStageLine && "ステージラインの取得に失敗");

	GameObject* pPlayerObj{ FindGameObject(player_) };
	Player* pPlayer{ dynamic_cast<Player*>(pPlayerObj) };
	wassert(pStageLine && "プレイヤーの取得に失敗");


	Vector3 playerPos{ pPlayer->Transform().GetPosition() };
	Vector3 targetPos{ playerPos + Vector3::Forward() * 30.0f };
	targetPos.y = pStageLine->GetPosY(targetPos);

	GetScene<PlayScene>().Instantiate<SpecialBall>();
}

void StageObjectManager::Release()
{
}
