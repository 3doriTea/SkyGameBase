#pragma once
#include <wtgb.h>

/// <summary>
/// ドラッグした方向が分かる3D UI
/// </summary>
class DragArrow : public GameObject
{
public:
	DragArrow(const EntityId _axis);
	~DragArrow();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	Vector2 direction_;  // 矢印ノーマル
	EntityId axis_;      // 軸
};
