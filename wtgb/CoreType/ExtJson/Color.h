#pragma once
#include "LibHeader/NlohmannJson.h"
#include "../Color.h"


namespace wtgb
{
	inline void to_json(json& j, const Color& c)
	{
		std::stringstream ss{};
		ss << std::hex << c.ToCode();
		j = ss.str();
	}

	inline void from_json(const json& j, Color& c)
	{
		c = Color{ std::stoul(j.get<std::string>(), nullptr, 16) };
	}
}
