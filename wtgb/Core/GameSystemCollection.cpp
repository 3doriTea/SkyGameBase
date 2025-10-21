#include "pch\pch.h"
#include "GameSystemCollection.h"
#include "IGameSystem.h"


wtgb::GameSystemCollection::~GameSystemCollection()
{
	callFrameIndexes_.clear();
	callCycleIndexes_.clear();

	for (auto& pGameSystem : gameSystems_)
	{
		delete pGameSystem;
		pGameSystem = nullptr;
	}
	gameSystems_.clear();
}

void wtgb::GameSystemCollection::UpdateForEach(const Indexes& _indexRef)
{
	for (const auto index : _indexRef)
	{
		gameSystems_[index]->Update();
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
