#include "pch/pch.h"
#include "StageObjectManager.h"
#include "../SampleScene/Player.h"
#include "StageLine.h"
#include "SpecialBall.h"
#include "PlayScene.h"
#include "SpecialBoom.h"

namespace
{
	// スポーンするまでのインターバル秒数
	const float SPAWN_INTERVAL_SEC{ 5.0f };

	// 拡散する角度 (degree)
	const float CONE_ANGLE_DEG{ 10.0f };

	// 拡散する円の等分割角度 (degree)
	const float DIVISION_ANGLE{ 30.0f };
}


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
	player_{ _player },
	spawnTimeLeftSec_{ SPAWN_INTERVAL_SEC }
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
	using namespace DirectX;

	const float dt{ System().Get<GameTime>().GetDeltaTime() };

	spawnTimeLeftSec_ -= dt;
	// まだスポーンのタイミングが来ていないなら
	if (spawnTimeLeftSec_ > 0.0f)
	{
		return;  // 回帰
	}
	// スポーンのタイミングなら
	spawnTimeLeftSec_ += SPAWN_INTERVAL_SEC;


	GameObject* pStageLineObj{ FindGameObject(stageLine_) };
	StageLine* pStageLine{ dynamic_cast<StageLine*>(pStageLineObj) };
	wassert(pStageLine && "ステージラインの取得に失敗");

	GameObject* pPlayerObj{ FindGameObject(player_) };
	Player* pPlayer{ dynamic_cast<Player*>(pPlayerObj) };
	wassert(pPlayer && "プレイヤーの取得に失敗");

	RigidBody& playerRB{ pPlayer->GetComponent<RigidBody>() };

	float speed{ XMVectorGetX(XMVector3Length(playerRB.GetVelocity())) };

	Vector3 playerPos{ pPlayer->Transform().GetPosition() };
	Vector3 targetPos{ playerPos + Vector3::Forward() * (speed * 10.0f + 100.0f) };
	targetPos.y = pStageLine->GetPosY(targetPos) + 30.0f;

	GetScene<PlayScene>().Instantiate<SpecialBoom>(targetPos, GetEntityId(), player_);

	Fire();
}

void StageObjectManager::Release()
{
}

void StageObjectManager::Fire()
{
	using namespace DirectX;

	GameObject* pPlayerObj{ FindGameObject(player_) };
	Player* pPlayer{ dynamic_cast<Player*>(pPlayerObj) };
	wassert(pPlayer && "プレイヤーの取得に失敗");

	RigidBody& playerRB{ pPlayer->GetComponent<RigidBody>() };


	Vector3 playerPos{ pPlayer->Transform().GetPosition() };
	Vector3 targetPos{ playerPos + Vector3::Forward() * 5.0f };

	Matrix4x4 mRotX{ XMMatrixRotationX(XMConvertToRadians(CONE_ANGLE_DEG)) };

	Vector3 vSrc{ playerRB.GetVelocity() };

	for (float angle = 0.0f; angle < XM_2PI; angle += XMConvertToRadians(DIVISION_ANGLE))
	{
		Matrix4x4 mRotZ{ XMMatrixRotationZ(angle) };

		Vector3 v{ XMVector3TransformCoord(vSrc, mRotX * mRotZ) };
		v.z = vSrc.z;

		GetScene<PlayScene>().Instantiate<SpecialBall>(targetPos, v);
	}
}
