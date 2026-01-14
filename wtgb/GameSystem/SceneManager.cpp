#include "pch\pch.h"
#include "SceneManager.h"
#include "Core/GameScene.h"
#include "GameTime.h"

wtgb::SceneManager::SceneManager() :
	pCurrent_{ nullptr },
	pToNext_{ nullptr },
	system_{ nullptr }
{
}

wtgb::SceneManager::~SceneManager()
{
}

wtgb::Result wtgb::SceneManager::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	GameScene::cachedSystem_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::SceneManager::Update(const ViewerUpdate& _system)
{
	if (pToNext_)
	{
		_system.Get<GameTime>().SetTimeStopped(true);

		SAFE_DELETE(pCurrent_);
		pCurrent_ = pToNext_;
		pToNext_ = nullptr;

		pCurrent_->cachedSystem_ = system_;
		pCurrent_->Start();  // シーン開始処理

		_system.Get<GameTime>().SetTimeStopped(false);
	}
	if (pCurrent_)
	{
		pCurrent_->Update();  // シーン更新処理
	}
}

void wtgb::SceneManager::End()
{
	SAFE_DELETE(pCurrent_);
	SAFE_DELETE(pToNext_);
}

void wtgb::SceneManager::RequestClearComponents()
{
	system_.Get<ComponentManager>().ClearComponents();
}
