#pragma once
#include <wtgb.h>

class TitleScene : public GameScene
{
public:
	TitleScene();
	~TitleScene();

	void Start() override;
	void Update() override;
};
