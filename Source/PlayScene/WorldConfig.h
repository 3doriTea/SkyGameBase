#pragma once
#include <wtgb.h>

/// <summary>
/// ワールドの設定
/// </summary>
struct WorldConfig
{
	float safeZoneXMin;      // 横最小値
	float safeZoneXMax;      // 横最大値
	float eggGetDistance;    // キャラエッグの回収可能距離
	Vector3 lightDirection;  // 平行光線(光源)の方向
	float gravity;           // 重力加速度
	struct
	{
		float polePosX;      // ポールを立てるx座標
	} lift;  // リフト
	struct
	{
		// X座標はステージサイズの半分 == 真ん中
		float startPositionY;  // プレイヤーが生まれる座標
		float startPositionZ;  // プレイヤーが生まれる座標
	} player;
	std::string bgmFilePath;  // 再生する音楽のファイルパス
};
