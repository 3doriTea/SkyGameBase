#include "pch\pch.h"
#include "ComponentManager.h"

wtgb::ComponentManager::ComponentManager()
{
}

wtgb::ComponentManager::~ComponentManager()
{
}

wtgb::Result wtgb::ComponentManager::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::ComponentManager::Update(const ViewerUpdate& _system)
{
	for (auto& typeToPool : typeToPools_)
	{
		typeToPool.second->Update();
	}
}

void wtgb::ComponentManager::End()
{
}

void wtgb::ComponentManager::ReleaseAll()
{
}

void wtgb::ComponentManager::UpdateAll()
{
}
