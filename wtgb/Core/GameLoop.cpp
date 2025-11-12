#include "pch\pch.h"
#include "GameLoop.h"
#include "IGame.h"
#include "WTGBAssert.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/ComponentManager.h"

wtgb::GameLoop::GameLoop() :
	isRunning_{ false },
	deltaTime_{ 0.0f }
{
}

wtgb::GameLoop::~GameLoop()
{
}

wtgb::Result wtgb::GameLoop::RunLoop(GameSystemCollection* _pGameSystemRegister)
{
	if (_pGameSystemRegister == nullptr)
	{
		wassert(_pGameSystemRegister && "pGameSystemCollectionが nullptrだった");
		return Result::Code::Error;
	}
	GameSystemCollection::GameSystemInitViewer gameSystemViewer{ _pGameSystemRegister };

	GameSystemCollection::ComponentPoolAccessor componentPools{ _pGameSystemRegister };

	isRunning_ = true;

	while (isRunning_)
	{
		_pGameSystemRegister->UpdateCycle();

		// フレーム呼び出しのタイミングならフレームも更新
		if (gameSystemViewer.Get<GameTime>().IsFrameDue())
		{
			_pGameSystemRegister->UpdateFrame();
		}

		if (gameSystemViewer.Get<ComponentManager>().NeedsClearComponents())
		{
			componentPools.ForEachAll([](IComponentPool* pComponentPool)
				{
					pComponentPool->Clear();
				});
		}
	}

	return Result::Code::Ok;
}

void wtgb::GameLoop::Stop()
{
	isRunning_ = false;
}
