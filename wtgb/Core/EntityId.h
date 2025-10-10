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

	//using EntityId = uint64_t;

	/*struct EntityId
	{

	};*/
}
