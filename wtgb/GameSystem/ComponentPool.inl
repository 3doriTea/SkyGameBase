#include "ComponentPool.h"
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
template<typename T, typename ...Args>
ComponentT& wtgb::ComponentPool<ComponentT>::Add(const EntityId _entityId, const Args& ...args)
{
	pool_[_entityId.index] = T{ args... };
	return pool_[_entityId.index];
}

template<typename ComponentT>
wtgb::ComponentPool<ComponentT>::Pool::iterator wtgb::ComponentPool<ComponentT>::begin()
{
	return pool_.begin();
}
