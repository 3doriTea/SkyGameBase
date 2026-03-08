#include "pch\pch.h"
#include "PlayScene.h"

#include "State/PlayState.h"
#include "WaterSphere.h"
#include "Player.h"
#include "CameraController.h"
#include "../TitleScene/TitleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"
#include "StageObjectManager.h"
#include "ControlUI.h"
#include "Lift/Lift.h"
#include "SkySphere.h"

#include "SMF/SMFPlayer.h"
#include "DropCloud.h"
#include "UI/CountDown.h"
#include "UI/SpeedMessage.h"
#include "SpeedController.h"

#include "Utility/Mathf.h"
#include "UI/MiniChara.h"

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
	EntityId playState{ Instantiate<PlayState>() };

	Instantiate<ControlUI>();
	Instantiate<CountDown>();

	EntityId stageLine{ Instantiate<StageLine>() };

	EntityId smfPlayer{ Instantiate<SMFPlayer>("Sound/entertainer.mid") };

	// TODO: ステージライン作ったらリフト作る
	Instantiate<Lift>(stageLine);
	
	float startPositionX{ Mathf::Lerp(worldConfig_.safeZoneXMin, worldConfig_.safeZoneXMax, 0.5f) };

	EntityId player{ Instantiate<Player>(INVALID_ENTITY, Vector3{ startPositionX, 30.0f, 5.0f }, playState) };
	Instantiate<StageObjectManager>(stageLine, player, playState);
	Instantiate<CameraController>();

	EntityId speedController{ Instantiate<SpeedController>(player) };
	EntityId dropCloud{ Instantiate<DropCloud>(smfPlayer, player, stageLine, playState, speedController) };

	Instantiate<SpeedMessage>(speedController);

	Instantiate<SkySphere>();
	
	Instantiate<MiniChara>(dropCloud, smfPlayer);

	// TODO: 当たったら倒れる看板を作る
}

void PlayScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<TitleScene>();
	}
	if (input.IsKeyDown(KeyCode::R))
	{
		System().Get<SceneManager>().Move<PlayScene>();
	}

	if (input.IsKeyDown(KeyCode::Escape))
	{
		Game::Exit();
	}
}
