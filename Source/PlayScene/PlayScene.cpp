#include "pch\pch.h"
#include "PlayScene.h"

#include "WaterSphere.h"
#include "Player.h"
#include "CameraController.h"
#include "../TitleScene/TitleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"
#include "StageObjectManager.h"
#include "ControlUI.h"
#include "Lift/Lift.h"

#include "SMF/SMFPlayer.h"
#include "DropCloud.h"

#include "Utility/Mathf.h"

PlayScene::PlayScene() : GameScene
{
	GameScene::Config
	{

	}
},
	worldConfig_
	{
		.safeZoneXMin = 0.0f,
		.safeZoneXMax = 400.0f,
		.eggGetDistance = 10.0f,
	}
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Start()
{
	Instantiate<ControlUI>();

	Instantiate<CameraController>();
	EntityId stageLine{ Instantiate<StageLine>() };

	EntityId smfPlayer{ Instantiate<SMFPlayer>("Sound/entertainer.mid") };

	// ステージライン作ったらリフト作る
	Instantiate<Lift>(stageLine);
	//Instantiate<TestBillBoard>();
	
	float startPositionX{ Mathf::Lerp(worldConfig_.safeZoneXMin, worldConfig_.safeZoneXMax, 0.5f) };

	EntityId player{ Instantiate<Player>(INVALID_ENTITY, Vector3{ startPositionX, 30.0f, 5.0f }) };
	Instantiate<StageObjectManager>(stageLine, player);

	Instantiate<DropCloud>(smfPlayer, player, stageLine);
}

void PlayScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<TitleScene>();
	}
}
