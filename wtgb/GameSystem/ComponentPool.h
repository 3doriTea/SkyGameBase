#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/IComponent.h"

namespace
{
	const size_t CAPACITY_SIZE{ 1024 };
}

namespace wtgb
{
	template<typename T>
	concept ComponentT = std::is_base_of_v<IComponent, T>;

	template<ComponentT T>
	class ComponentPool
	{
		using Pool = std::vector<ComponentT>;
	public:
		ComponentPool();
		virtual ~ComponentPool() {}

	protected:
		Pool::iterator begin() { pool_.begin(); }
		Pool::iterator end() { pool_.end(); }
		Pool::const_iterator begin() const { pool_.begin(); }
		Pool::const_iterator end() const { pool_.end(); }

	private:
		Pool pool_;
		uint32_t currentVersion_;
	};
}

template<wtgb::ComponentT T>
inline wtgb::ComponentPool<T>::ComponentPool() :
	currentVersion_{}
{
}
