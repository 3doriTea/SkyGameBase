#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// エンティティの最大数
	/// </summary>
	static const size_t ENTITY_CAPACITY
	{
#include "../_Config/EntityCapacity.value"
	};
}
