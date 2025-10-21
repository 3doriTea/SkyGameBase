#pragma once
#include "pch/pch.h"
#include "Entity.h"

namespace wtgb
{
	class World
	{
	public:
		struct Config
		{
			size_t entitiesCapacity;
		};

	public:
		World();
		~World();

	private:
		std::vector<EntityId> entities_;
	};
}
