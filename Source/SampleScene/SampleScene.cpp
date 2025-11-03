#include "pch\pch.h"
#include "SampleScene.h"

#include "GameSystem/Camera.h"

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
	System().Get<Camera>().position_ = { 0, 0, -10.0f };
	System().Get<Camera>().targetPosition_ = { 0, 0, 0 };

	Instantiate<Player>();

}
