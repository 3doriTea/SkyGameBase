#pragma once
#include <wtgb.h>


/// <summary>
/// このゲームのスコア情報
/// </summary>
struct GameScore
{
	int32_t presentCount;  // 獲得したプレゼント数
	int32_t allyCount;     // 獲得した仲間数
	float timeDifference;  // ゴールタイムの時間差
};
