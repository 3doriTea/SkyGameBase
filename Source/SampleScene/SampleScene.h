#pragma once
#include "wtgb.h"

class SampleScene : public wtgb::GameScene
{
public:
	SampleScene();
	~SampleScene() {}

	void Start() override;
	void Update() override;
};
