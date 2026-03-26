#pragma once
#include <wtgb.h>


/// <summary>
/// 一番背景の青空
/// </summary>
class SkySphere : public GameObject
{
public:
	SkySphere(const EntityId _cameraEntity, const float _angleYRadian = 0.0f);
	~SkySphere();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	float angleYRadian_;  // Y軸の回転
};
