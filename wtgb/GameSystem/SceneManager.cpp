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
	if (pToNext_)
	{
		SAFE_DELETE(pCurrent_);
		pCurrent_ = pToNext_;
		pToNext_ = nullptr;
	}
	if (pCurrent_)
	{
		pCurrent_->Update();
	}
}

void wtgb::SceneManager::End()
{
	SAFE_DELETE(pCurrent_);
	SAFE_DELETE(pToNext_);
}
