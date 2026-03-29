#include "pch/pch.h"
#include "StageObjectManager.h"
#include "Player.h"
#include "StageLine.h"
#include "SpecialBall.h"
#include "PlayScene.h"
#include "SpecialBoom.h"
#include "CharaBall.h"
#include "CharaEgg.h"
#include "Systems/ScoreManager.h"

#include "State/PlayState.h"

namespace
{
	// スポーンするまでのインターバル秒数
	const float SPAWN_INTERVAL_SEC{ 5.0f };

	// 拡散する角度 (degree)
	const float CONE_ANGLE_DEG{ 10.0f };

	// 拡散する円の等分割角度 (degree)
	const float DIVISION_ANGLE{ 30.0f };

	// 出現する最低限の距離
	const float SPAWN_DISTANCE_OFFSET{ 100.0f };

	// 出現する距離でスピードの係数
	const float SPAWN_DISTANCE_PER_SPEED{ 10.0f };

	// 出現する地面からの高さ
	const float SPAWN_HEIGHT{ 20.0f };

	// ボールが出現する距離
	const float SPECIAL_BALL_DINSTANCE{ 5.0f };
}


StageObjectManager::StageObjectManager(
	const EntityId _stageLine,
	const EntityId _player,
	const EntityId _playState) :
	GameObject{ "StageObjectManager.json" },
	stageLine_{ _stageLine },
	player_{ _player },
	playState_{ _playState },
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

	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンの取得に失敗するとなにもできない
	}

	PlayState* playState{ dynamic_cast<PlayState*>(FindGameObject(playState_)) };
	if (playState && playState->GetState() != PlayState::Type::Falling)
	{
		return;  // 下山中以外は無視
	}

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
	Vector3 targetPos{ playerPos + Vector3::Forward() * (speed * SPAWN_DISTANCE_PER_SPEED + SPAWN_DISTANCE_OFFSET) };
	targetPos.y = pStageLine->GetPosY(targetPos) + SPAWN_HEIGHT;

	pPlayScene->Instantiate<CharaEgg>(targetPos, GetEntityId(), player_);
}

void StageObjectManager::Release()
{
}

void StageObjectManager::Fire()
{
	using namespace DirectX;
	
	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンが取得できなければ何もしない
	}

	GameObject* pPlayerObj{ FindGameObject(player_) };
	Player* pPlayer{ dynamic_cast<Player*>(pPlayerObj) };
	wassert(pPlayer && "プレイヤーの取得に失敗");

	RigidBody& playerRB{ pPlayer->GetComponent<RigidBody>() };


	Vector3 playerPos{ pPlayer->Transform().GetPosition() };
	Vector3 targetPos{ playerPos + Vector3::Forward() * SPECIAL_BALL_DINSTANCE };

	Matrix4x4 mRotX{ XMMatrixRotationX(XMConvertToRadians(CONE_ANGLE_DEG)) };

	Vector3 vSrc{ playerRB.GetVelocity() };

	for (float angle = 0.0f; angle < XM_2PI; angle += XMConvertToRadians(DIVISION_ANGLE))
	{
		Matrix4x4 mRotZ{ XMMatrixRotationZ(angle) };

		Vector3 v{ XMVector3TransformCoord(vSrc, mRotX * mRotZ) };
		v.z = vSrc.z;

		pPlayScene->Instantiate<CharaBall>(targetPos, v, player_);

		System().Get<ScoreManager>().Ref([](GameScore& _score)
			{
				// 増えた仲間の数を加算
				_score.allyCount += 1;
			});
	}
}
