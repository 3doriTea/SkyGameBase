#include "pch\pch.h"
#include "PlayScene.h"

#include "../SampleScene/Player.h"

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
}

void PlayScene::Update()
{
}
