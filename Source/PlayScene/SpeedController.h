#pragma once
#include <wtgb.h>

/// <summary>
/// スピードの種類
/// </summary>
enum struct SpeedType
{
	Stop,       // 止まっている
	TooSlow,    // 遅すぎ
	Good,       // 良い速度
	Excissive,  // 速すぎ
};

/// <summary>
/// <para>速度を操作するやつ</para>
/// <para>※Speed = m/f</para>
/// </summary>
class SpeedController : public GameObject
{
public:
	SpeedController(const EntityId _player);
	~SpeedController();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// グレイアウト(回りが白黒になるやつ)の比率を取得
	/// </summary>
	/// <returns>0.0f ~ 1.0f</returns>
	float GetGreyOutRatio() const;
	/// <summary>
	/// 完全に気絶状態か取得
	/// </summary>
	/// <returns>気絶状態 true / false</returns>
	bool IsGLOC() const;

	/// <summary>
	/// 現在のスピード種類を取得
	/// </summary>
	/// <returns>スピードの種類</returns>
	SpeedType GetSpeedType() const;

private:
	void OnLoadParam(const json& _json);

private:
	float speedStopMin_;   // 動かない判定の最低値
	float speedGoodMin_;   // 適正スピードの最低値
	float speedHighMin_;   // 早すぎるスピード
	float speedGLOCLine_;  // 気絶が起きる-スピードの最大値

	float currentSpeedValue_;  // 現在の速度
	float previousSpeedValue_;  // 前回のフレームの速度

	EntityId player_;      // プレイヤー
};
