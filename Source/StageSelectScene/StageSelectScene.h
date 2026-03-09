#pragma once
#include <wtgb.h>

class StageSelectScene : public GameScene
{
public:
	StageSelectScene(GameScene::Config&& _config);
	~StageSelectScene();

	void Start() override;
	void Update() override;
};

