#pragma once
#include "Core/GameObject.h"

class Player : public wtgb::GameObject
{
public:
	Player();
	~Player();

	void Init() override;
	void Update() override;
};
