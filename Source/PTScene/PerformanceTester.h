#pragma once
#include <wtgb.h>

/// <summary>
/// パフォーマンスをテストするクラス
/// </summary>
class PerformanceTester
{
public:
	PerformanceTester();
	~PerformanceTester();

	/// <summary>
	/// 1フレームの更新処理
	/// </summary>
	/// <param name="_deltaTime">フレーム間時間</param>
	void Update(const float _deltaTime);
	/// <summary>
	/// 現在のパフォーマンスを履歴に追加
	/// </summary>
	/// <param name="_desc">追加する説明</param>
	void Stamp(const std::string_view _desc);
	/// <summary>
	/// 履歴をテキストファイルとして出力する
	/// </summary>
	/// <param name="_filePath">テキストファイルのパス</param>
	void Dump(const fs::path& _filePath);

	/// <summary>
	/// FPSを取得する
	/// </summary>
	/// <returns>FPS値</returns>
	inline uint32_t GetFPS() const { return frameCountPrev_; }

private:
	uint32_t frameCounter_;             // フレームのカウント
	uint32_t frameCountPrev_;           // 前のフレームのカウント
	float timeLeft_;                    // 1秒間を計測するタイマー
	std::vector<std::string> history_;  // パフォーマンスのダンプ履歴
};

