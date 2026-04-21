#pragma once
#include <wtgb.h>

/// <summary>
/// パフォーマンスをテストするシーン
/// </summary>
class PTScene : public GameScene
{
public:
	PTScene(GameScene::Config&& _config);
	~PTScene();

	void Start() override;
	void Update() override;
};
