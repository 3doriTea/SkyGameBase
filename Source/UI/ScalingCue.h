#pragma once
#include <wtgb.h>
#include "BaseCue.h"


/// <summary>
/// 拡縮アニメーションするヒントUI
/// </summary>
class ScalingCue : public BaseCue
{
public:
	using BaseCue::BaseCue;
	inline ~ScalingCue() {}

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_pLayout">調整するレイアウト</param>
	/// <param name="_animRatio">アニメーションレート</param>
	void Draw(UI::LayoutConfig* _pLayout, const float _animRatio) override;
};
