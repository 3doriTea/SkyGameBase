#pragma once
#include <wtgb.h>
#include "SpeedType.h"
#include "ISpeedController.h"

/// <summary>
/// <para>速度を操作するやつ</para>
/// <para>※Speed = m/f</para>
/// </summary>
class SpeedController : public GameObject, public ISpeedController
{
public:
	SpeedController();
	~SpeedController();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// グレイアウト(回りが白黒になるやつ)の比率を取得
	/// </summary>
	/// <returns>0.0f ~ 1.0f</returns>
	float GetGreyOutRatio() const override;
	/// <summary>
	/// 完全に気絶状態か取得
	/// </summary>
	/// <returns>気絶状態 true / false</returns>
	bool IsGLOC() const override;

	/// <summary>
	/// 現在のスピード種類を取得
	/// </summary>
	/// <returns>スピードの種類</returns>
	SpeedType GetSpeedType() const override;

	/// <summary>
	/// スピード(1フレーム当たりの移動量)
	/// </summary>
	/// <param name="_perFrame">m/f</param>
	void SetSpeed(const float _perFrame);

private:
	void OnLoadParam(const json& _json);

private:
	float speedStopMin_;   // 動かない判定の最低値
	float speedGoodMin_;   // 適正スピードの最低値
	float speedHighMin_;   // 早すぎるスピード
	float speedGLOCLine_;  // 気絶が起きる-スピードの最大値

	float currentSpeedValue_;  // 現在の速度
	float previousSpeedValue_;  // 前回のフレームの速度
};
