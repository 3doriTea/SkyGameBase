#include "pch\pch.h"
#include "ComponentManager.h"

wtgb::ComponentManager::ComponentManager() :
	system_{ nullptr },
	prevEntityId_{ wtgb::INVALIED_ID }
{
}

wtgb::ComponentManager::~ComponentManager()
{
}

wtgb::Result wtgb::ComponentManager::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::ComponentManager::Update(const ViewerUpdate& _system)
{
	//for (auto& pool : pools_)
	//{
	//	//pool->;
	//}
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

wtgb::EntityId wtgb::ComponentManager::GenerateEntity()
{
	prevEntityId_ = entityGenerator_.Generate();
	return prevEntityId_;
}

void wtgb::ComponentManager::RemoveEntity(const EntityId _entityId)
{
	entityGenerator_.Remove(_entityId);
}
