#pragma once
#include <wtgb.h>

/// <summary>
/// スペシャルボール
/// </summary>
class SpecialBall : public GameObject
{
public:
	SpecialBall(const Vector3& _position, const Vector3& _velocity);
	~SpecialBall();

	void Init() override;
	void Update() override;
	void Release() override;
};
