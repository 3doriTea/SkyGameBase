#pragma once
#include <wtgb.h>


/// <summary>
/// タイトルシーンの設定
/// </summary>
struct TitleSceneConfig
{

};

/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene : public GameScene
{
public:
	TitleScene(GameScene::Config&& _config);
	~TitleScene();

	void Start() override;
	void Update() override;
};
