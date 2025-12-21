#include "pch/pch.h"
#include "TitleNeco.h"
#include "../SMF/SMFPlayer.h"
#include "../UI/DragCircle.h"
#include "../UI/Button.h"
#include "TitleScene.h"
#include "../PlayScene/PlayScene.h"

TitleNeco::TitleNeco(const EntityId _dragCircle) :
	GameObject{ "Simple.json" },
	hImages_{},
	isDrag_{ false },
	moveRatio_{},
	dragCircle_{ _dragCircle },
	playButton_{ INVALID_ENTITY }
{
}

TitleNeco::~TitleNeco()
{
}

void TitleNeco::Init()
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };
	const Vector2Int screenSizeInt{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2 screenSize{ static_cast<float>(screenSizeInt.x), static_cast<float>(screenSizeInt.y) };
	TitleScene& titleScene{ GetScene<TitleScene>() };

	//dragCircle_ = GetScene<SampleScene>().Instantiate<DragCircle>(centerPosition, 30);
	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };

	pDragCircle->SetRadius(100);

	fs::path dir{ "./Image/Title" };

	hImages_[I_HAND] = rc.LoadTexture(dir / "TitleNeco-Hand.png");
	hImages_[I_HANG] = rc.LoadTexture(dir / "TitleNeco-Hang.png");
	hImages_[I_NORM] = rc.LoadTexture(dir / "TitleNeco-Norm.png");

	playButton_ = titleScene.Instantiate<Button>();
	Button* pPlayButton{ dynamic_cast<Button*>(FindGameObject(playButton_)) };

	TextureHandle hOff{ rc.LoadTexture(dir / "PlayButton-Off.png") };
	pPlayButton->SetOffImage(hOff);
	TextureHandle hOn{ rc.LoadTexture(dir / "PlayButton-On.png") };
	pPlayButton->SetOnImage(hOn);

	Vector2Int imageSize{ rc.GetTexture(hOff)->GetImageSizePix() };
	pPlayButton->SetPosition(screenSizeInt / 2 - imageSize / 2);
	pPlayButton->SetSize(imageSize);

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject("SMFPlayer")) };
	if (pSMFPlayer)
	{
		Audio& audio{ System().Get<Audio>() };

		// ノーツ再生時の音源読み込み && セット
		pSMFPlayer->SetToneAudioHandle(
			audio.Load("Sound/385892__spacether__262312__steffcaffrey__cat-meow1.mp3"));

		// ノーツの処理を登録
		pSMFPlayer->OnNote([pSMFPlayer](Note _note)
			{
				if (_note.channel == 0x03)
				{
					_note.noteNumber -= 12 * 2;
					pSMFPlayer->PlayTone(_note);
				}
			});


		// 再生！
		pSMFPlayer->Play();
	}
}

void TitleNeco::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };

	const float dt{ System().Get<GameTime>().GetDeltaTime() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	const Vector2Int screenSizeInt{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2 screenSize{ static_cast<float>(screenSizeInt.x), static_cast<float>(screenSizeInt.y) };

	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };

	if (pDragCircle && pDragCircle->IsDrag())
	{
		Vector2Int displacement{ pDragCircle->GetDisplacement() };
		LOGFLN("displacement:({}, {})", displacement.x, displacement.y);
		moveRatio_ += static_cast<float>(-displacement.y) / screenSize.y;
	}
	else
	{
		if (moveRatio_ < 0.5f)
		{
			moveRatio_ -= dt / 3.0f;
		}
		else
		{
			moveRatio_ += dt / 3.0f;
		}
	}
	moveRatio_ = min(max(moveRatio_, 0.0f), 1.0f);

	if (pDragCircle)
	{
		isDrag_ = pDragCircle->IsDrag();
		pDragCircle->SetPosition({ 430, static_cast<int>((screenSize.y / 1.3f) * (1.0f - moveRatio_)) });
	}

	UI::LayoutConfig config{};
	context.SetRefLayout(&config);

	TextureHandle hBodyImage
	{
		isDrag_
		? hImages_[I_HANG]
		: hImages_[I_NORM]
	};

	config.order(10);

	config.scale({ screenSize.x, screenSize.y });
	config.position({ 0, screenSize.y * (1.0f - moveRatio_) });
	context.DrawImage(hBodyImage);

	config.position({ 0, (screenSize.y / 2.0f) * (1.0f - moveRatio_) });
	context.DrawImage(hImages_[I_HAND]);

	Button* pPlayButton{ dynamic_cast<Button*>(FindGameObject(playButton_)) };
	wassert(pPlayButton && "プレイシーンへ行くボタンがないよ！");

	if (pPlayButton)
	{
		if (pPlayButton->IsPushedFrame())
		{
			System().Get<SceneManager>().Move<PlayScene>();
		}
	}
}

void TitleNeco::Release()
{
}

