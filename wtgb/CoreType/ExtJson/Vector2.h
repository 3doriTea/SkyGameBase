#pragma once
#include "LibHeader/NlohmannJson.h"
#include "../Vector2.h"


namespace wtgb
{
	inline void to_json(json& j, const Vector2& v)
	{
		j = json{ { "x", v.x }, { "y", v.y } };
	}

	inline void from_json(const json& j, Vector2& v)
	{
		if (j.is_array())
		{
			v.x = j.at(Vector2::AT_X).get<float>();
			v.y = j.at(Vector2::AT_Y).get<float>();
		}
		else
		{
			v.x = j.at("x").get<float>();
			v.y = j.at("y").get<float>();
		}
	}
}
