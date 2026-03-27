#pragma once
#include <cmath>

namespace wtgb
{
	/// <summary>
	/// <para>Easing関数詰め合わせセット</para>
	/// <para>https://easings.net/ja</para>
	/// </summary>
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

		/// <summary>
		/// <para>ずんずんずんずぎゅばーーー</para>
		/// <para>REF: https://easings.net/ja#easeInElastic</para>
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		inline static float InElastic(float x)
		{
			const float C4{ 2.0f * PI / 3.0f };

			return x == 0.0f
				? 0.0f
				: x == 1.0f
				? 1.0f
				: -std::powf(2.0f, 10.0f * x - 10.0f) * std::sinf((x * 10.0f - 10.75f) * C4);
		}

		/// <summary>
		/// <para>すぅぅんういいい</para>
		/// <para>REF: https://easings.net/ja#easeInBack</para>
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		inline static float InBack(float x)
		{
			const float C1{ 1.70158f };
			const float C3{ C1 + 1.0f };

			return C3 * x * x * x - C1 * x * x;
		}
	};
}
