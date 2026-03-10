#include "pch\pch.h"
#include "ComponentManager.h"

wtgb::ComponentManager::ComponentManager() :
	system_{ nullptr },
	prevEntityId_{ wtgb::INVALIED_ID },
	componentPoolAccessor_{ nullptr },
	needsClearComponents_{ false }
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
}

void wtgb::ComponentManager::End()
{
}

wtgb::EntityId wtgb::ComponentManager::GenerateEntity()
{
	prevEntityId_ = entityGenerator_.Generate();
	return prevEntityId_;
}

void wtgb::ComponentManager::RemoveEntity(const EntityId _entityId)
{
	toRemoveEntityIndices_.push_back(_entityId.index);
	// TODO: これもしかしたらリセット時にするほうがいいかもーーーーー
}

void wtgb::ComponentManager::ResetToRemoveEntityIndices()
{
	for (const uint32_t index : toRemoveEntityIndices_)
	{
		entityGenerator_.RemoveAt(index);
	}
	toRemoveEntityIndices_.clear();
}

void wtgb::ComponentManager::RemoveAllEntity()
{
	entityGenerator_.RemoveAll();
	needsClearComponents_ = false;
}
