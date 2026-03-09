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
	return Result::Code::Ok;
}

void wtgb::SceneManager::Update(const ViewerUpdate& _system)
{
	if (pToNext_)
	{
		// シーン読み込み中は時間を止める
		_system.Get<GameTime>().SetTimeStopped(true);

		pCurrent_.reset();
		pCurrent_ = std::move(pToNext_);
		pToNext_ = {};

		pCurrent_.get()->Start();  // シーン開始処理

		_system.Get<GameTime>().SetTimeStopped(false);
	}
	if (pCurrent_)
	{
		pCurrent_.get()->Update();  // シーン更新処理
	}
}

void wtgb::SceneManager::End()
{
	pCurrent_.reset();
	pToNext_.reset();
}

void wtgb::SceneManager::RequestClearComponents()
{
	system_.Get<ComponentManager>().ClearComponents();
}
