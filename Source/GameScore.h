#pragma once
#include <wtgb.h>


/// <summary>
/// このゲームのスコア情報
/// </summary>
struct GameScore
{
	/// <summary>
	/// ゲーム内スコアの種類
	/// </summary>
	using ScoreType = int32_t;
	/// <summary>
	/// ゲーム内スコアの種類
	/// </summary>
	enum ScoreType_ : ScoreType
	{
		ScoreType_PresentCount,    // 獲得したプレゼント数
		ScoreType_AllyCount,       // 獲得した仲間数
		ScoreType_TimeDifference,  // ゴールタイムの時間差
		ScoreType_Max,             // スコア種類の最大数
	};

	int32_t presentCount;  // 獲得したプレゼント数
	int32_t allyCount;     // 獲得した仲間数
	float timeDifference;  // ゴールタイムの時間差
};
