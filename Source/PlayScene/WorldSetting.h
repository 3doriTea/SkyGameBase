#pragma once

/// <summary>
/// ワールドの設定
/// </summary>
struct WorldConfig
{
	float safeZoneXMin;    // 横最小値
	float safeZoneXMax;    // 横最大値
	float eggGetDistance;  // キャラエッグの回収可能距離
	Vector3 lightDirection;  // 平行光線(光源)の方向
};
