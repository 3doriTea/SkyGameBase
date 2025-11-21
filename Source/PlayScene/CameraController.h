#pragma once
#include <wtgb.h>

class CameraController : public GameObject
{
public:
	CameraController();
	~CameraController();

	void Init() override;
	void Update() override;
	void Release() override {}

private:
	float speedBoost_;
	Vector2Int prevMousePos_;  // 前フレームのマウススクリーン座標
};
