#include "pch/pch.h"
#include "TitleScene.h"

#include "TitleMountain.h"
#include "TitleNeco.h"
#include "TitleCamera.h"
#include "SMF/SMFPlayer.h"
#include "UI/DragCircle.h"

#include "MusicPlayer.h"

#include "PlayScene/PlayScene.h"
#include "ResultScene/ResultScene.h"
#include "Systems/ScoreManager.h"

#include "SkySphere/SkySphere.h"


TitleScene::TitleScene(GameScene::Config&& _config) :
	GameScene{ std::move(_config) }
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Start()
{
	Instantiate<TitleMountain>();

	Instantiate<MusicPlayer>();

	EntityId dragCircle{ Instantiate<DragCircle>() };
	EntityId titleNeco{ Instantiate<TitleNeco>(dragCircle) };
	EntityId camera{ Instantiate<TitleCamera>(titleNeco) };

	System().Get<Camera>().position_ = { 200, -140, 440.0f };
	System().Get<Camera>().targetPosition_ = { 0, -160.0, 400.0f };
	
	Instantiate<SkySphere>(camera, DirectX::XM_PI / 2.0f);
}

void TitleScene::Update()
{
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	if (input.IsKeyDown(KeyCode::T))
	{
		System().Get<SceneManager>().Move<PlayScene>();
	}

	Camera& camera{ System().Get<Camera>() };

	if (input.IsKeyDown(KeyCode::Escape))
	{
		Game::Exit();
	}

	if (input.IsKeyDown(KeyCode::Alpha0))
	{
		System().Get<ScoreManager>().Ref([](GameScore& _score)
			{
				_score.allyCount = 72;
				_score.presentCount = 104;
				_score.timeDifference = 123;
			});
		System().Get<SceneManager>().Move<ResultScene>();
	}
}
