#include "pch\pch.h"
#include "Lift.h"
#include "../StageLine.h"
#include "LiftPole.h"
#include "PlayScene/PlayScene.h"

namespace
{
	static float POLE_DISTANCE{ 100 };  // ここのポールの距離
	static float POLE_POS_X{ 10.0f };  // ポールを配置するx座標
}

Lift::Lift(EntityId _stage) :
	GameObject{ "Simple.json" },
	stage_{ _stage }
{
	// ポールを建てるx軸だけ指定しておく
	Transform().SetPosition({ POLE_POS_X, 0, 0 });
}

Lift::~Lift()
{
}

void Lift::Init()
{
	StageLine* pStage{ dynamic_cast<StageLine*>(FindGameObject(stage_)) };
	wassert(pStage && "ステージラインオブジェクトが見つからない");

	const float STAGE_LENGTH_Z{ pStage->GetStageLengthZ() };
	for (float currZ = 0.0f; currZ < STAGE_LENGTH_Z; currZ += POLE_DISTANCE)
	{
		// ポールを作っていく
		Vector3 position
		{
			Transform().GetPosition().y,
			pStage->GetPosY(Vector3::Forward() * currZ),
			currZ
		};

		GetScene<PlayScene>().Instantiate<LiftPole>(position);
	}
}

void Lift::Update()
{
	
}

void Lift::Release()
{
}
