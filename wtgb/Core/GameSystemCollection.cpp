#include "pch\pch.h"
#include "GameSystemCollection.h"

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

void wtgb::GameSystemCollection::UpdateForEach(const std::vector<int>& _indexRef)
{
	for (const auto index : _indexRef)
	{
		gameSystems_[index]->Update();
	}
}

void wtgb::GameSystemCollection::InitForEachAll()
{
	for (auto pGameSystem : gameSystems_)
	{
		pGameSystem->Init();
	}
}

void wtgb::GameSystemCollection::EndForEachAll()
{
	for (auto pGameSystem : gameSystems_)
	{
		pGameSystem->Init();
	}
}
