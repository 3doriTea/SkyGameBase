#pragma once
#include "pch/pch.h"
#include "Entity.h"
#include "GameSystem/IComponentPool.h"

namespace wtgb
{
	class ComponentManager
	{
	public:
		ComponentManager();
		~ComponentManager();

		void ReleaseAll();

		template<typename T>
		void Release(const EntityId _entityId);

		template<typename T>
		void Register(const EntityId _entityId);

		template<typename T>
		T& Get(const EntityId _entityId);

		template<typename T>
		const T& Get(const EntityId _entityId) const;

	private:
		std::map<std::type_index, IComponentPool*> pools_;
	};
}

template<typename T>
inline void wtgb::ComponentManager::Release(const EntityId _entityId)
{
}

template<typename T>
inline void wtgb::ComponentManager::Register(const EntityId _entityId)
{
}


template<typename T>
T& wtgb::ComponentManager::Get(const EntityId _entityId)
{
	return pools_.at(typeid(T));
}

template<typename T>
inline const T& wtgb::ComponentManager::Get(const EntityId _entityId) const
{
	return pools_.at(typeid(T));
}
