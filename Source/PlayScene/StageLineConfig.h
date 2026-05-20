#pragma once
#include <wtgb.h>

/// <summary>
/// ステージの設定
/// </summary>
struct StageLineConfig
{
	float goalHeight;      // ゴールの低さ
	float goalPosY;        // ゴールの座標y
	float randRangeX;      // ランダム幅の範囲x
	float randRangeY;      // ランダム幅の範囲y
	float goalSizeZ;       // ゴールの平地幅z
	float goalWallHeight;  // ゴールの壁z
	Vector3 stageScale;    // ステージオブジェクト自体のサイズ
	float uvScaleRatioX;        // x軸のuvスケール比率
};
