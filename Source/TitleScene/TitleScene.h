#pragma once
#include <wtgb.h>

class TitleScene : public GameScene
{
public:
	TitleScene(GameScene::Config&& _config);
	~TitleScene();

	void Start() override;
	void Update() override;
};
