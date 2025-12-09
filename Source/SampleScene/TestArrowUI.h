#pragma once
#include <wtgb.h>

class TestArrowUI : public GameObject
{
public:
	TestArrowUI();
	~TestArrowUI();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	TextureHandle hArrowTexture_;  // テスト用矢印の画像
};
