#pragma once
#include "Helper/CommonGameComponent.h"
#include "ItemAnim/ItemType.h"

class COMPONENT(ItemAnim)
{
	friend CPItemAnim;

public:
	class SETTER(ItemAnim)
	{
		SETTER_HEAD(ItemAnim)

		SETTER_PARAM(ItemType, itemType)
		SETTER_PARAM(float, totalTime)
	};

	ItemAnim();
	~ItemAnim();

	void Init(wtgb::ViewerCached _system) override;

	/// <summary>
	/// アニメーションの再生レートを取得する
	/// </summary>
	/// <returns>再生中の位置 0.0 ~ 1.0</returns>
	inline float GetRatio() const { return timerUp_ / totalTime_; }

	/// <summary>
	/// アニメーションが終了したか
	/// </summary>
	/// <returns>終了した true / false</returns>
	inline bool IsFinished() const { return isFinished_; }

	/// <summary>
	/// 総再生時間を設定する
	/// </summary>
	/// <param name="_totalTime">総再生時間(秒)</param>
	inline void SetTotalTime(const float _totalTimeSec) { totalTime_ = _totalTimeSec; }

	/// <summary>
	/// 開始地点
	/// </summary>
	/// <param name="_position"></param>
	inline void SetStartPos(const wtgb::Vector3& _position) { startPos_ = _position; }
	/// <summary>
	/// 終了地点
	/// </summary>
	/// <param name="_position"></param>
	inline void SetEndPos(const wtgb::Vector3& _position) { endPos_ = _position; }

private:
	ItemType itemType_;       // 種類
	float totalTime_;         // 総再生時間
	float timerUp_;          // 残り時間
	wtgb::Vector3 startPos_;  // 開始地点
	wtgb::Vector3 endPos_;    // 終了地点
	bool isFinished_;         // アニメーションが終了したか
};
