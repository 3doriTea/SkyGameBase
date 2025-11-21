#include "pch\pch.h"
#include "PlayScene.h"

#include "../SampleScene/Player.h"
#include "CameraController.h"
#include "../SampleScene/SampleScene.h"
#include "StageLine.h"
#include "TestBillBoard.h"

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
	
	EntityId pRootPlayer{ Instantiate<Player>(INVALID_ENTITY, Vector3::Zero()) };
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				Instantiate<Player>(pRootPlayer, Vector3{ i * 3.0f, k * 5.0f + 10.0f, j * 3.0f });
			}
		}
	}
	
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
