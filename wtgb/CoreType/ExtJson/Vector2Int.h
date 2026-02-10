#pragma once
#include "LibHeader/NlohmannJson.h"
#include "../Vector2Int.h"


namespace wtgb
{
	inline void to_json(json& j, const Vector2Int& v)
	{
		j = json{ { "x", v.x }, { "y", v.y } };
	}

	inline void from_json(const json& j, Vector2Int& v)
	{
		if (j.is_array())
		{
			v.x = j.at(Vector2Int::AT_X).get<int>();
			v.y = j.at(Vector2Int::AT_Y).get<int>();
		}
		else
		{
			v.x = j.at("x").get<int>();
			v.y = j.at("y").get<int>();
		}
	}
}
