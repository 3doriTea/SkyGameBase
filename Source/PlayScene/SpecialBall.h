#pragma once
#include <wtgb.h>

/// <summary>
/// スペシャルボール
/// </summary>
class SpecialBall : public GameObject
{
public:
	SpecialBall(const Vector3& _position);
	~SpecialBall();

	void Init() override;
	void Update() override;
	void Release() override;
};
