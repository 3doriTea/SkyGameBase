#include "pch\pch.h"
#include "SampleScene.h"

#include "Player.h"

using namespace wtgb;

SampleScene::SampleScene() : GameScene
{
	GameScene::Config
	{
	}
}
{
}

void SampleScene::Start()
{
	Instantiate<Player>();
}
