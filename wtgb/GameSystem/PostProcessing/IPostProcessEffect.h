#pragma once
#include "PostEffectType.h"

namespace wtgb
{
	class IPostProcessEffect
	{
	public:
		inline IPostProcessEffect() {}
		inline virtual ~IPostProcessEffect() {}

		/// <summary>
		/// ポストエフェクトの種類を取得
		/// </summary>
		/// <returns>ポストエフェクトの種類</returns>
		virtual PostEffectType GetType() = 0;
		/// <summary>
		/// 描画処理
		/// </summary>
		virtual void Render() = 0;
	};
}
