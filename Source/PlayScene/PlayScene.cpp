#include "pch\pch.h"
#include "PlayScene.h"

#include "WaterSphere.h"
#include "../SampleScene/Player.h"
#include "CameraController.h"
#include "../SampleScene/SampleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"

#include "Utility/Mathf.h"

PlayScene::PlayScene() : GameScene
{
	GameScene::Config
	{

	}
}
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Start()
{
	Instantiate<CameraController>();
	Instantiate<StageLine>();

	//Instantiate<TestBillBoard>();
	
	//EntityId pRootPlayer{ Instantiate<Player>(INVALID_ENTITY, Vector3{ 2.5f, 5.0f, 5.0f }) };
	//EntityId pRootPlayer{ Instantiate<Player>(INVALID_ENTITY, Vector3{ 2.5f, -180.0f, 300.0f }) };
	EntityId pRootPlayer{ Instantiate<Player>(INVALID_ENTITY, Vector3{ 2.5f, -180.0f, 300.0f }) };
	/*for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				Instantiate<Player>(pRootPlayer, Vector3{ i * 3.0f, k * 5.0f + 10.0f, j * 3.0f });
			}
		}
	}*/

	Mathf::Randomer random{};

#if 1
	for (int i = 0; i < 0; i++)
	{
		float r1{ random.Rand() };
		float r2{ random.Rand() };
		Instantiate<WaterSphere>(Vector3{ r1 * 300.0f + 50.0f, 5.0f, r2 * 10.0f });
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
		System().Get<SceneManager>().Move<SampleScene>();
	}
}
