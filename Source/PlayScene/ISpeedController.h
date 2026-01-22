#pragma once
#include "SpeedType.h"


/// <summary>
/// スピード操作オブジェクトのインタフェース
/// </summary>
class ISpeedController
{
public:
	inline ISpeedController() {}
	inline virtual ~ISpeedController() {}

	/// <summary>
	/// グレイアウト(回りが白黒になるやつ)の比率を取得
	/// </summary>
	/// <returns>0.0f ~ 1.0f</returns>
	inline virtual float GetGreyOutRatio() const = 0;
	/// <summary>
	/// 完全に気絶状態か取得
	/// </summary>
	/// <returns>気絶状態 true / false</returns>
	inline virtual bool IsGLOC() const = 0;

	/// <summary>
	/// 現在のスピード種類を取得
	/// </summary>
	/// <returns>スピードの種類</returns>
	inline virtual SpeedType GetSpeedType() const = 0;
};
