#include "pch\pch.h"
#include "GameSystemCollection.h"
#include "IGameSystem.h"
#include "WTGBAssert.h"

#include "GameSystem/ComponentManager.h"
#include "GameSystem/Debug.h"

wtgb::GameSystemCollection::GameSystemCollection()
{
}

wtgb::GameSystemCollection::~GameSystemCollection()
{
	callFrameIndexes_.clear();
	callCycleIndexes_.clear();

	// TODO: ここで例外でる調べる
	for (auto& pGameSystem : gameSystems_)
	{
		pGameSystem.reset();
	}
	gameSystems_.clear();
}

void wtgb::GameSystemCollection::UpdateForEach(const Indexes& _indexRef)
{
	GameSystemUpdateViewer viewer{ (this) };
	for (const auto index : _indexRef)
	{
		gameSystems_[index].get()->Update(viewer);
	}
}

void wtgb::GameSystemCollection::InitForEachAll()
{
	GameSystemInitViewer viewer{ this };
	for (const auto& pGameSystem : gameSystems_)
	{
		pGameSystem.get()->Init(viewer);
	}
}

void wtgb::GameSystemCollection::EndForEachAll()
{
	for (const auto& pGameSystem : gameSystems_)
	{
		pGameSystem.get()->End();
	}
}

wtgb::GameSystemCollection::GameSystemCachedViewer
	wtgb::GameSystemCollection::GameSystemInitViewer::GetCache() const
{
	return { GetAccess() };
}

void wtgb::GameSystemCollection::ComponentPoolAccessor::ForEachAll(const ForEachCallback& _callback)
{
	// コンポーネントプールだけアクセス
	for (const auto index : GetAccess()->componentPoolIndexes_)
	{
		IComponentPool* pComponentPool{ dynamic_cast<IComponentPool*>(GetAccess()->gameSystems_[index].get()) };
		wassert(pComponentPool != nullptr && "ComponentPoolではないゲームシステムにアクセスしようとした");

		_callback(pComponentPool);
	}
}
