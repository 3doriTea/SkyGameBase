#pragma once
#include <wtgb.h>
#include "WaterPlane/WaterMesh.h"

/// <summary>
/// 水面オブジェクト
/// </summary>
class WaterPlane : public GameObject
{
public:
	WaterPlane(const Vector3& _localPos, const Vector2Int _size);
	~WaterPlane();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	std::vector<float> pointsHeight_;  // 各波頂点の高さ y軸 (0 ~ 1)
	WaterMesh waterMesh_;              // 水面のメッシュ情報
};
