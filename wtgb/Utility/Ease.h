#pragma once
#include <cmath>

namespace wtgb
{
	class Ease
	{
	private:
		static const float PI;

	public:
		inline static float OutElastic(float x)
		{
			const float C4{ (2.0f * PI) / 3.0f };

			return x == 0.0f
			? 0.0f
			: x == 1.0f
			? 1.0f
			: std::powf(2.0f, -10.0f * x) * std::sinf((x * 10.0f - 0.75f) * C4) + 1.0f;
		}
	};
}
