#pragma once
#include <wtgb.h>

/// <summary>
/// リフトのループたん
/// </summary>
class LiftLoop : public GameObject
{
public:
	LiftLoop(const Vector3& _position, const EntityId _lift);
	~LiftLoop() {}

	void Init() override {}
	void Update() override;
	void Release() override {}

private:
	EntityId lift_;
};
