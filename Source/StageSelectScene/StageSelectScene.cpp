#include "StageSelectScene.h"
#include "PlayScene/PlayScene.h"

StageSelectScene::StageSelectScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) }
{
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Start()
{
	// 選択ボール
}

void StageSelectScene::Update()
{
	const auto& input{ System().Get<Input>().Getter() };
	auto& sceneManager{ System().Get<SceneManager>() };

	if (input.IsKeyDown(KeyCode::F))
	{
		sceneManager.Move<PlayScene>();
	}
}
