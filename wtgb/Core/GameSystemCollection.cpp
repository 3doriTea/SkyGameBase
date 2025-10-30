#include "pch\pch.h"
#include "GameSystemCollection.h"
#include "IGameSystem.h"

#include "GameSystem/Debug.h"

wtgb::GameSystemCollection::GameSystemCollection()
{
}

wtgb::GameSystemCollection::~GameSystemCollection()
{
	callFrameIndexes_.clear();
	callCycleIndexes_.clear();

	for (auto& pGameSystem : gameSystems_)
	{
		SAFE_DELETE(pGameSystem);
	}
	gameSystems_.clear();
}

void wtgb::GameSystemCollection::UpdateForEach(const Indexes& _indexRef)
{
	GameSystemUpdateViewer viewer{ this };
	for (const auto index : _indexRef)
	{
		gameSystems_[index]->Update(viewer);
	}
}

void wtgb::GameSystemCollection::InitForEachAll()
{
	GameSystemInitViewer viewer{ this };
	for (auto pGameSystem : gameSystems_)
	{
		pGameSystem->Init(viewer);
	}
}

void wtgb::GameSystemCollection::EndForEachAll()
{
	for (auto pGameSystem : gameSystems_)
	{
		pGameSystem->End();
	}
}

wtgb::GameSystemCollection::GameSystemCachedViewer
	wtgb::GameSystemCollection::GameSystemInitViewer::GetCache() const
{
	return { GetAccess() };
}
