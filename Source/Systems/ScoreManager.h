#pragma once
#include <wtgb.h>
#include "GameScore.h"


/// <summary>
/// スコアを管理するシステム
/// </summary>
class ScoreManager : public IGameSystem
{
public:
	ScoreManager();
	~ScoreManager();

	const CallType GetCallType() override { return CallType::DoNotUpdate; }
	Result Init(const ViewerInit& _viewer) override;
	void Update(const ViewerUpdate& _system) override;
	void End() override;

	/// <summary>
	/// ゲームスコアをリセットする
	/// </summary>
	void ResetGameScore();

	/// <summary>
	/// ゲームスコアを参照する
	/// </summary>
	/// <param name="_callback">ゲームスコアのコールバック関数 void(GameScore&)</param>
	inline void Ref(const std::function<void(GameScore&)>& _callback) { _callback(gameScore_); }

	/// <summary>
	/// 現在のスコア値を取得
	/// </summary>
	/// <returns>現在のスコア値</returns>
	uint64_t GetCurrentScore() const { return currentScore_; }
	/// <summary>
	/// 現在のスコア値を設定する
	/// </summary>
	/// <param name="_value">設定するスコア値</param>
	void SetCurrentScore(const uint64_t _value) { currentScore_ = _value; }
	/// <summary>
	/// 現在のスコア値に加算する
	/// </summary>
	/// <param name="_value">加算するスコア値</param>
	void AddCurrentScore(const uint64_t _value) { currentScore_ += _value; }
private:
	uint64_t currentScore_;  // 現在のスコア値
	uint64_t maxScore_;      // スコアの最大値

	GameScore gameScore_;  // ゲームのスコア
};
