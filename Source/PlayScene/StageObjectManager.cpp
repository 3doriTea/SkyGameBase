#include "pch/pch.h"
#include "StageObjectManager.h"
#include "../SampleScene/Player.h"
#include "StageLine.h"
#include "SpecialBall.h"


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


	GameObject* pPlayerObj{ FindGameObject(player_) };
}

void StageObjectManager::Release()
{
}
