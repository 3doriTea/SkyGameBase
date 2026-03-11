#include "pch\pch.h"
#include "Lift.h"
#include "../StageLine.h"
#include "LiftPole.h"
#include "LiftLoop.h"
#include "LiftChair.h"
#include "PlayScene/PlayScene.h"

namespace
{
	static float POLE_DISTANCE{ 100 };  // ここのポールの距離
	static float POLE_POS_X{ 10.0f };  // ポールを配置するx座標
	static float POLE_HEIGHT{ 20.0f };  // ポールの地面からラインまでの高さ
}

Lift::Lift(EntityId _stage) :
	GameObject{ "Simple.json" },
	stage_{ _stage },
	rotationSpeedPerSec_{ 6.0f },
	loopPole_{ INVALID_ENTITY, INVALID_ENTITY }
{
	// ポールを建てるx軸だけ指定しておく
	Transform().SetPosition({ POLE_POS_X, 0, 0 });
}

Lift::~Lift()
{
}

void Lift::Init()
{
	PlayScene* pPlayScene{ GetScene<PlayScene>() };
	wassert(pPlayScene && u8"プレイシーンの取得に失敗");

	if (pPlayScene == nullptr)
	{
		return;  // プレイシーンの取得に失敗したときはなにもできない
	}

	StageLine* pStage{ dynamic_cast<StageLine*>(FindGameObject(stage_)) };

	if (pStage == nullptr)
	{
		wassert(false && "ステージラインオブジェクトが見つからない");
		return;
	}

	const float STAGE_LENGTH_Z{ pStage->GetStageLengthZ() };
	float currZ = 0.0f;

	EntityId parentEntity{ GetEntityId() };
	//EntityId parentEntity{ INVALID_ENTITY };
	
	EntityId instantiatedEntity{ INVALID_ENTITY };

	// 最初のループはじめを設置 (ポールと重複する)
	loopPole_[LOOP_POLE_UPPER] = pPlayScene->Instantiate<LiftLoop>(GetPolePosition(currZ), parentEntity);
	
	while (currZ < STAGE_LENGTH_Z)
	{
		// ポールを立てていく
		instantiatedEntity = pPlayScene->Instantiate<LiftPole>(GetPolePosition(currZ), parentEntity);
		poles_.push_back(instantiatedEntity);
		currZ += POLE_DISTANCE;
	}

	currZ -= POLE_DISTANCE;
	
	// 最後のループ端を設置 (ポールと重複する)
	loopPole_[LOOP_POLE_LOWER] = pPlayScene->Instantiate<LiftLoop>(GetPolePosition(currZ), parentEntity);

	for (float z = 0; z < 1000.0f; z += 50.0f)
	{
		pPlayScene->Instantiate<LiftChair>(parentEntity, z, false);
		pPlayScene->Instantiate<LiftChair>(parentEntity, z, true);
	}
}

void Lift::Update()
{
	
}

void Lift::Release()
{
}

Vector3 Lift::GetPolePosition(const float _z)
{
	StageLine* pStage{ dynamic_cast<StageLine*>(FindGameObject(stage_)) };
	wassert(pStage && "ステージラインオブジェクトが見つからない");

	return Vector3
	{
		0.0f,
		pStage->GetPosY(Vector3::Forward() * _z),
		_z
	};
}

bool Lift::TryGetLinePosition(const float _z, Vector3* _pPosition)
{
	// 範囲始まりにいるポールのインデクス
	const int POLE_INDEX{ static_cast<int>(_z / POLE_DISTANCE) };
	
	// Zが0未満 や 最後のポールより奥 は範囲外のため失敗
	if (_z < 0 || (poles_.size() - 1) <= POLE_INDEX)
	{
		return false;
	}

	GameObject* pBegin{ FindGameObject(poles_.at(POLE_INDEX).entityId) };
	GameObject* pEnd{ FindGameObject(poles_.at(POLE_INDEX + 1).entityId) };


	// ポール内のどの位置にいるかの率
	const float RATIO{ std::fmodf(_z, POLE_DISTANCE) / POLE_DISTANCE };



	Vector3 beginPos{ pBegin->Transform().GetPositionWorld() };
	Vector3 endPos{ pEnd->Transform().GetPositionWorld() };

	//beginPos = beginPos + Vector3::Up() * POLE_HEIGHT;
	//endPos = endPos + Vector3::Up() * POLE_HEIGHT;

	// 2点間を線形補間して座標を求める
	*_pPosition = Mathf::Lerp(
		beginPos,
		endPos,
		RATIO);

	_pPosition->y += POLE_HEIGHT;

	return true;  // 成功
}

Lift::Pole::Pole(const EntityId _entityId) :
	entityId{ _entityId }
{
}
