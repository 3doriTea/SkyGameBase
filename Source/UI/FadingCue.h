#pragma once
#include <wtgb.h>
#include "BaseCue.h"


/// <summary>
/// 透明度アニメーションをするヒントUI
/// </summary>
class FadingCue : public BaseCue
{
public:
	using BaseCue::BaseCue;
	inline ~FadingCue() {}

private:
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_pLayout">調整するレイアウト</param>
	/// <param name="_animRatio">アニメーションレート</param>
	void Draw(UI::LayoutConfig* _pLayout, const float _animRatio) override;
};

