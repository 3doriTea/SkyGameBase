#pragma once
#include <wtgb.h>

class PlayScene : public GameScene
{
public:
	PlayScene();
	~PlayScene();

	void Start() override;
	void Update() override;
};
