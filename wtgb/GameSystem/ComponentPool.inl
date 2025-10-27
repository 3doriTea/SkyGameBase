#include "ComponentPool.h"
template<typename ComponentT>
wtgb::Result wtgb::ComponentPool<ComponentT>::Init(const ViewerInit& _viewer)
{
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
inline ComponentT& wtgb::ComponentPool<ComponentT>::Add(const EntityId _entityId)
{
	pool_[_entityId.index] = {};
	return pool_[_entityId.index];
}
