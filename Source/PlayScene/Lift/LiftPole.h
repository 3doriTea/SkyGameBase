#pragma once
#include <wtgb.h>

class LiftPole : public GameObject
{
public:
	LiftPole(const Vector3& _position, const EntityId _lift);
	~LiftPole() {}

	void Init() override {}
	void Update() override {}
	void Release() override {}
};
