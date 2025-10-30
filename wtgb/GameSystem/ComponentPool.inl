#include "ComponentPool.h"
#include "ComponentManager.h"

template<typename ComponentT>
wtgb::Result wtgb::ComponentPool<ComponentT>::Init(const ViewerInit& _viewer)
{
	pool_.resize(wtgb::ENTITY_CAPACITY);

	system_ = _viewer.GetCache();

	Init();
	return Result::Code::Ok;
}


template<typename ComponentT>
void wtgb::ComponentPool<ComponentT>::Update(const ViewerUpdate& _system)
{
	Update();
}

template<typename ComponentT>
inline ComponentT* wtgb::ComponentPool<ComponentT>::Get(const EntityId _entityId)
{
	// 無効なEntityId なら取得しない
	if (IsInvalidEntity(_entityId))
	{
		useFlag_[_entityId.index] = false;
		return nullptr;
	}

	if (useFlag_[_entityId.index])
	{
		return &pool_[_entityId.index];
	}
	else
	{
		return nullptr;
	}
}

template<typename ComponentT>
inline void wtgb::ComponentPool<ComponentT>::Remove(const EntityId _entityId)
{
	// 使わないからフラグ降ろすだけ
	useFlag_[_entityId.index] = false;
}

template<typename ComponentT>
inline bool wtgb::ComponentPool<ComponentT>::IsInvalidEntity(const EntityId _entityId)
{
	return System().Get<ComponentManager>().IsInvalidId(_entityId);
}

template<typename ComponentT>
template<typename T, typename ...Args>
ComponentT& wtgb::ComponentPool<ComponentT>::Add(const EntityId _entityId, const Args& ...args)
{
	pool_[_entityId.index] = T{ args... };
	// 使っているからフラグを立てる
	useFlag_[_entityId.index] = true;
	return pool_[_entityId.index];
}
