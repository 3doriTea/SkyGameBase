#pragma once
#include "LibHeader/NlohmannJson.h"
#include "../Vector2Int.h"

namespace wtgb
{
	inline void to_json(json& j, const Vector2Int& v)
	{
		j = json{ { v.x, v.y } };
	}

	inline void from_json(const json& j, Vector2Int& v)
	{
		v.x = j.at(0).get<int>();
		v.y = j.at(1).get<int>();
	}
}
