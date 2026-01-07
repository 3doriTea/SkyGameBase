#pragma once
#include "Helper/CommonGameComponent.h"
#include "../Systems/CPItemAnim.h"

enum struct ItemType : uint32_t
{
	PresentRedSphere,  // 赤丸プレゼント
};

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

	void Init(wtgb::ViewerCached _system) override;

	/// <summary>
	/// アニメーションの再生レートを取得する
	/// </summary>
	/// <returns>再生中の位置 0.0 ~ 1.0</returns>
	inline float GetRatio() const { return timeLeft_ / totalTime_; }

	/// <summary>
	/// アニメーションが終了したか
	/// </summary>
	/// <returns>終了した true / false</returns>
	inline bool IsFinished() const { return isFinished_; }

private:
	ItemType itemType_;       // 種類
	float totalTime_;         // 総再生時間
	float timeLeft_;          // 残り時間
	wtgb::Vector3 startPos_;  // 開始地点
	wtgb::Vector3 endPos_;    // 終了地点
	bool isFinished_;         // アニメーションが終了したか
};
