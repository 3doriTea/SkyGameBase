#pragma once
#include <pch/pch.h>

namespace wtgb
{
	/// <summary>
	/// エンティティの識別値
	/// </summary>
	union EntityId
	{
		uint32_t version;
		uint32_t index;
	};

	struct EntityData
	{
		EntityId self;
		EntityId parent;
		EntityId next;
	};
}
