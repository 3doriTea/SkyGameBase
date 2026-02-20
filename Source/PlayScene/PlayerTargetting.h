#pragma once
#include <wtgb.h>

/// <summary>
/// プレイヤーがターゲットまで突撃する挙動の計算パラメータ
/// </summary>
struct PLAYER_TARGETTING_PARAMS
{
	Vector3 playerPos{};       // プレイヤーの座標
	Vector3 playerVelocity{};  // プレイヤーの現在の速度
	Vector3 targetPos{};       // ターゲットの座標
	float gravity{};           // 重力加速度
};

/// <summary>
/// プレイヤーをターゲットまで突撃させる処理クラス
/// </summary>
class PlayerTargeting
{
public:
	inline PlayerTargeting() {}
	inline ~PlayerTargeting() {}

	/// <summary>
	/// ターゲットまで突撃させるときの速度を求める
	/// </summary>
	/// <param name="params">計算パラメータ</param>
	/// <returns>いい感じの速度</returns>
	Vector3 GetToTargetVelocity(const PLAYER_TARGETTING_PARAMS& params);
};
