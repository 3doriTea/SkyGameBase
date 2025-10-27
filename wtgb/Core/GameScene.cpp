#include "pch\pch.h"
#include "GameScene.h"
#include "GameComponent/GameObject.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/SceneManager.h"

wtgb::GameScene::GameScene(Config&& _config) :
	cachedSystem_{ nullptr }
{
}

wtgb::GameScene::~GameScene()
{
}
