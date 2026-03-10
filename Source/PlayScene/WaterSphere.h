#pragma once
#include <wtgb.h>

/// <summary>
/// 水の球
/// </summary>
class WaterSphere : public GameObject
{
public:
	WaterSphere(const Vector3 _localPos);
	~WaterSphere();

	void Init() override;
	void Update() override;
	void Release() override;
};
