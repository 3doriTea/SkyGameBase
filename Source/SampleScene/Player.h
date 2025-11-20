#pragma once
#include <wtgb/wtgb.h>

class Player : public GameObject
{
public:
	Player(const EntityId _parentId, const Vector3 _localPos);
	~Player();

	void Init() override;
	void Update() override;
	void Release() override {}

private:
	float angle_;
};
