#pragma once
#include <wtgb/wtgb.h>

class Player : public GameObject
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;

private:
	float angle_;
};
