#pragma once
#include <wtgb.h>

class LiftPole : public GameObject
{
public:
	LiftPole(const Vector3& _position);
	~LiftPole() {}

	void Init() override {}
	void Update() override {}
	void Release() override {}
};
