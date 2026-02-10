#pragma once
#include "LibHeader/NlohmannJson.h"
#include "../Vector3.h"


namespace wtgb
{
	inline void to_json(json& j, const Vector3& v)
	{
		j = json{{ v.x, v.y, v.z }};
	}

	inline void from_json(const json& j, Vector3& v)
	{
		if (j.is_array())
		{
			v.x = j.at(Vector3::AT_X).get<float>();
			v.y = j.at(Vector3::AT_Y).get<float>();
			v.z = j.at(Vector3::AT_Z).get<float>();
		}
		else
		{
			v.x = j.at("x").get<float>();
			v.y = j.at("y").get<float>();
			v.z = j.at("z").get<float>();
		}
	}
}
