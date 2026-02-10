#include "pch\pch.h"
#include "GameScene.h"
#include "GameComponent/GameObject.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/SceneManager.h"


wtgb::GameScene::GameScene(Config&& _config)
{
}

wtgb::GameScene::~GameScene()
{
}

wtgb::ViewerCached wtgb::GameScene::cachedSystem_{ nullptr };
