#include "pch\pch.h"
#include "SceneManager.h"
#include "Core/GameScene.h"

wtgb::SceneManager::SceneManager() :
	pCurrent_{ nullptr },
	pToNext_{ nullptr }
{
}

wtgb::SceneManager::~SceneManager()
{
}

wtgb::Result wtgb::SceneManager::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::SceneManager::Update(const ViewerUpdate& _system)
{
	if (pCurrent_)
	{
		pCurrent_->Update
	}
}

void wtgb::SceneManager::End()
{
}
