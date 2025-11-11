#pragma once
#include <wtgb.h>

class CameraController : public GameObject
{
public:
	CameraController();
	~CameraController();

	void Init() override;
	void Update() override;

private:
	Vector2Int prevMousePos_;  // 前フレームのマウススクリーン座標
};
