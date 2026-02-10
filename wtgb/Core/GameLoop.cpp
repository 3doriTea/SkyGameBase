#include "pch\pch.h"
#include "GameLoop.h"
#include "IGame.h"
#include "WTGBAssert.h"

#include "GameSystem/GameTime.h"
#include "GameSystem/ComponentManager.h"


wtgb::GameLoop::GameLoop() :
	isRunning_{ false }
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

		// 全消しが発生したら
		if (gameSystemViewer.Get<ComponentManager>().NeedsClearComponents())
		{
			gameSystemViewer.Get<ComponentManager>().RemoveAllEntity();

			componentPools.ForEachAll([](IComponentPool* pComponentPool)
				{
					pComponentPool->Clear();
				});
		}
		else  // 破棄対象のエンティティが存在するなら破棄処理していく
		{
			const std::vector<uint32_t>& toRemoveEntityIndices
			{
				gameSystemViewer.Get<ComponentManager>().GetToRemoveEntityIndices()
			};

			// 破棄処理していく
			componentPools.ForEachAll([&toRemoveEntityIndices](IComponentPool* pComponentPool)
				{
					for (const uint32_t i : toRemoveEntityIndices)
					{
						pComponentPool->ClearAt(i);
					}
				});

			gameSystemViewer.Get<ComponentManager>().ResetToRemoveEntityIndices();
		}
	}

	return Result::Code::Ok;
}

void wtgb::GameLoop::Stop()
{
	isRunning_ = false;
}
