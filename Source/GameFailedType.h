#pragma once
#include <wtgb.h>


/// <summary>
/// 失敗の種類
/// </summary>
using GameFailedType = int32_t;

/// <summary>
/// 失敗の種類
/// </summary>
enum GameFailedType_ : GameFailedType
{
	GameFailedType_None,          // 失敗していない
	GameFailedType_OutStopper,    // ストッパーを超えてしまった
	GameFailedType_OutFallStart,  // スタート地点の後ろに行ってしまった
	GameFailedType_Max,           // 失敗種類の最大数
};
