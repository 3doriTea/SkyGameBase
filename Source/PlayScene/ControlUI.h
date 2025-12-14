#pragma once
#include "pch/pch.h"
#include <wtgb.h>

/// <summary>
/// 操作を促すUI
/// </summary>
class ControlUI : public GameObject
{
public:
	ControlUI();
	~ControlUI();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	TextureHandle hCenterCircleImage_;  // 中心のプレイヤー操作円の画像ハンドル
};
