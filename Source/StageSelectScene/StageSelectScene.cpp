#include "StageSelectScene.h"
#include "PlayScene/PlayScene.h"

StageSelectScene::StageSelectScene() : GameScene
{
	GameScene::Config{}
}
{
}

StageSelectScene::~StageSelectScene()
{
}

void StageSelectScene::Start()
{
	// ëIëÉ{Å[Éã
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
