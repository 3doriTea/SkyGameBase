#include "pch\pch.h"
#include "Lift.h"
#include "../StageLine.h"
#include "LiftPole.h"
#include "LiftLoop.h"
#include "PlayScene/PlayScene.h"

namespace
{
	static float POLE_DISTANCE{ 100 };  // ここのポールの距離
	static float POLE_POS_X{ 10.0f };  // ポールを配置するx座標
}

Lift::Lift(EntityId _stage) :
	GameObject{ "Simple.json" },
	stage_{ _stage },
	rotationSpeedPerSec_{ 6.0f }
{
	// ポールを建てるx軸だけ指定しておく
	Transform().SetPosition({ POLE_POS_X, 0, 0 });
}

Lift::~Lift()
{
}

void Lift::Init()
{
	PlayScene& playScene{ GetScene<PlayScene>() };

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
	
	// 最初のループはじめを設置
	playScene.Instantiate<LiftLoop>(GetPolePosition(currZ), parentEntity);

	currZ += POLE_DISTANCE;
	
	while (currZ < STAGE_LENGTH_Z)
	{
		// ポールを立てていく
		playScene.Instantiate<LiftPole>(GetPolePosition(currZ), parentEntity);
		currZ += POLE_DISTANCE;
	}

	// 最後のループ端を設置
	playScene.Instantiate<LiftLoop>(GetPolePosition(currZ), parentEntity);
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
