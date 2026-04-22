#pragma once
#include <wtgb.h>
#include "PerformanceTester.h"

/// <summary>
/// ゲームのパフォーマンスを読み取るゲームオブジェクト
/// </summary>
class PerformanceReader : public GameObject
{
public:
	PerformanceReader();
	~PerformanceReader();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

private:
	PerformanceTester tester_;  // パフォーマンス計測
};
