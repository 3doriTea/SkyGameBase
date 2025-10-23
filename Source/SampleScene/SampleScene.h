#pragma once
#include "Core/GameScene.h"

class SampleScene : public wtgb::GameScene
{
public:
	using GameScene::GameScene;
	~SampleScene() {}

	void Start() override;
};
