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
		v.x = j.at(0).get<float>();
		v.y = j.at(1).get<float>();
		v.z = j.at(2).get<float>();
	}
}
