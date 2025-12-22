#include "pch\pch.h"
#include "PlayScene.h"

#include "WaterSphere.h"
#include "../SampleScene/Player.h"
#include "CameraController.h"
#include "../TitleScene/TitleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"
#include "StageObjectManager.h"
#include "ControlUI.h"
#include "Lift/Lift.h"

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

	// ステージライン作ったらリフト作る
	Instantiate<Lift>(stageLine);
	//Instantiate<TestBillBoard>();
	
	float startPositionX{ Mathf::Lerp(worldConfig_.safeZoneXMin, worldConfig_.safeZoneXMax, 0.5f) };

	EntityId player{ Instantiate<Player>(INVALID_ENTITY, Vector3{ startPositionX, 10.0f, 5.0f }) };
	Instantiate<StageObjectManager>(stageLine, player);

	Mathf::Randomer random{};

#if 1
	for (int i = 0; i < 0; i++)
	{
		float r1{ random.Rand() };
		float r2{ random.Rand() };
		Instantiate<WaterSphere>(Vector3{ r1 * 300.0f + 50.0f, 5.0f, r2 * 100.0f + 100.0f });
	}
#else
	for (int i = 0; i < 100; i++)
	{
		float r1{ random.Rand() };
		float r2{ random.Rand() };
		Instantiate<WaterSphere>(Vector3{ r1 * 300.0f + 50.0f, 5.0f, r2 * 10.0f });
		//Instantiate<WaterSphere>(Vector3{ 50.0f, 5.0f + i, 5.0f });
	}
#endif

	//for (int k = 0; k < 20; k++)
	//{
	//	for (int j = 0; j < 20; j++)
	//	{
	//		for (int i = 0; i < 20; i++)
	//		{
	//			Instantiate<Player>(pRootPlayer, Vector3{ i * 3.0f, k * 5.0f, j * 3.0f });
	//			//Instantiate<Player>(pRootPlayer, Vector3{ -i * 3.0f, k * 5.0f, -j * 3.0f });
	//		}
	//	}
	//}

}

void PlayScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<TitleScene>();
	}
}
