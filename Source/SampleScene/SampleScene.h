#pragma once
#include "wtgb.h"

class SampleScene : public wtgb::GameScene
{
public:
	SampleScene(GameScene::Config&& _config);
	~SampleScene() {}

	void Start() override;
	void Update() override;
};
