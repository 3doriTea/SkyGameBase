#pragma once
#include <wtgb.h>

/// <summary>
/// デバッグ用に座標点を表示する
/// </summary>
class DebugPoint : public GameObject
{
public:
	DebugPoint(const Vector3& _position, const float _scale);
	~DebugPoint();

	void Init() override;
};
