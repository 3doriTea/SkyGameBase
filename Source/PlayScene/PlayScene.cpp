#include "pch\pch.h"
#include "PlayScene.h"

#include "../SampleScene/Player.h"
#include "CameraController.h"

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
	//Instantiate<Player>();
	Instantiate<CameraController>();
}

void PlayScene::Update()
{
}
