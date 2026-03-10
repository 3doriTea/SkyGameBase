#include <cassert>

template<typename T>
inline T& wtgb::ComponentManager::Add(const EntityId _entityId)
{
	assert(entityGenerator_.IsInvalidId(_entityId) == false && "無効なエンティティIdが指定された");

	return system_.Get<typename T::PoolT>().Add(_entityId);
}

template<typename T>
T& wtgb::ComponentManager::Get(const EntityId _entityId)
{
	T* pComponent{ system_.Get<typename T::PoolT>().Get(_entityId) };
	return *pComponent;
}

template<typename T>
inline const T& wtgb::ComponentManager::Get(const EntityId _entityId) const
{
	const T* pComponent{ dynamic_cast<const T*>(typeToPools_.at(typeid(T))) };
	assert(pComponent && "指定したコンポーネントが見つからなかった");

	return *pComponent;
}
