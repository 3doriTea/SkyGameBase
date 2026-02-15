#pragma once
#include <wtgb.h>

class CircleHint : public GameObject
{
public:
	CircleHint();
	~CircleHint();

	void Init() override;
	void Update() override;
};
