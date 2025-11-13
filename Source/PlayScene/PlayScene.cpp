#include "pch\pch.h"
#include "PlayScene.h"

#include "../SampleScene/Player.h"
#include "CameraController.h"
#include "../SampleScene/SampleScene.h"

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
	Instantiate<Player>();
	Instantiate<CameraController>();
}

void PlayScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	if (input.IsKeyDown(KeyCode::F))
	{
		System().Get<SceneManager>().Move<SampleScene>();
	}
}
