#include "pch/pch.h"
#include "TitleNeco.h"
#include "../SMF/SMFPlayer.h"
#include "../UI/DragCircle.h"
#include "../UI/Button.h"
#include "TitleScene.h"
#include "../PlayScene/PlayScene.h"

// TODO: タイトル猫が持ちすぎてるから分ける

namespace
{
	static const int OFFSET_X{ 300 };
}

TitleNeco::TitleNeco(const EntityId _dragCircle) :
	GameObject{ "TitleNeco.json" },
	hImages_{},
	isDrag_{ false },
	moveRatio_{},
	dragPoint_{ _dragCircle },
	playButton_{ INVALID_ENTITY },
	playButtonShowPos_{},
	playToneAudioFile_{},
	hButtonOff_{},
	hButtonOn_{}
{
}

TitleNeco::~TitleNeco()
{
}

void TitleNeco::OnLoadParam(const json& _json)
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };

	wassert(_json.contains("necoImagePath") && "jsonにパラメータが含まれていない");
	const json& necoImagePath{ _json["necoImagePath"] };

	hImages_[I_HAND] = rc.LoadTexture(
		SafeGet<std::string>(necoImagePath, "hand"));
	hImages_[I_HANG] = rc.LoadTexture(
		SafeGet<std::string>(necoImagePath, "hang"));
	hImages_[I_NORM] = rc.LoadTexture(
		SafeGet<std::string>(necoImagePath, "norm"));
	
	wassert(_json.contains("playButtonImagePath") && "jsonにパラメータが含まれていない");
	const json& buttonImagePath{ _json["playButtonImagePath"] };

	hButtonOff_ = rc.LoadTexture(
		SafeGet<std::string>(buttonImagePath, "off"));
	hButtonOn_ = rc.LoadTexture(
		SafeGet<std::string>(buttonImagePath, "on"));

	playToneAudioFile_ = SafeGet<std::string>(_json, "playToneAudio");

	wassert(_json.contains("uiLayoutConfig") && "jsonにパラメータが含まれていない");
	const json& uiLayoutConfig{ _json["uiLayoutConfig"] };

	uiLayoutConfigOrder_ = SafeGet<int>(uiLayoutConfig, "order");
}

void TitleNeco::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	ResourceSystem& rc{ System().Get<ResourceSystem>() };
	const Vector2Int screenSizeInt{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2 screenSize{ static_cast<float>(screenSizeInt.x), static_cast<float>(screenSizeInt.y) };
	TitleScene& titleScene{ GetScene<TitleScene>() };

	//dragPoint_ = GetScene<SampleScene>().Instantiate<DragCircle>(centerPosition, 30);
	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragPoint_)) };

	pDragCircle->SetRadius(100);

#pragma region プレイボタン
	playButton_ = titleScene.Instantiate<Button>();
	Button* pPlayButton{ dynamic_cast<Button*>(FindGameObject(playButton_)) };

	pPlayButton->SetOffImage(hButtonOff_);
	pPlayButton->SetOnImage(hButtonOn_);

	Vector2Int imageSize{ rc.GetTexture(hButtonOff_)->GetImageSizePix() };
	pPlayButton->SetSize(imageSize);
	playButtonShowPos_ = screenSizeInt / 3;

	pPlayButton->SetInOnCursorFunc(
		[](const Vector2Int _pos, const Vector2Int _size, const Vector2Int _cursorPos) -> bool
		{
			const int PLAY_BUTTON_RADIUS{ 287 };
			const int PLAY_BUTTON_RADIUS_SQ{ PLAY_BUTTON_RADIUS * PLAY_BUTTON_RADIUS };

			Vector2Int begin{ _pos };
			Vector2Int end{ _pos + _size };
			Vector2Int center{ _pos + _size / 2 };
			Vector2Int diff{ center - _cursorPos };
			if ((diff.x * diff.x + diff.y * diff.y) > PLAY_BUTTON_RADIUS_SQ)
			{
				return false;  // 円の範囲外なら当たっていない
			}

			return begin.x <= _cursorPos.x && _cursorPos.x <= end.x
				&& begin.y <= _cursorPos.y && _cursorPos.y <= end.y;
		});
#pragma endregion

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject("SMFPlayer")) };
	if (pSMFPlayer)
	{
		Audio& audio{ System().Get<Audio>() };

		// ノーツ再生時の音源読み込み && セット
		pSMFPlayer->SetToneAudioHandle(audio.Load(playToneAudioFile_));

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

	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragPoint_)) };

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
		// TODO: ボタンドラッグ位置を確定させる
		isDrag_ = pDragCircle->IsDrag();
		pDragCircle->SetPosition({ 430 + OFFSET_X, static_cast<int>((screenSize.y / 1.3f) * (1.0f - moveRatio_)) });
	}

	UI::LayoutConfig config{};
	context.SetRefLayout(&config);

	TextureHandle hBodyImage
	{
		isDrag_
		? hImages_[I_HANG]
		: hImages_[I_NORM]
	};

	config.order(uiLayoutConfigOrder_);

	config.scale({ screenSize.x, screenSize.y });
	config.position({ OFFSET_X, screenSize.y * (1.0f - moveRatio_) });
	context.DrawImage(hBodyImage);

	config.position({ OFFSET_X, (screenSize.y / 2.0f) * (1.0f - moveRatio_) });
	context.DrawImage(hImages_[I_HAND]);

	Button* pPlayButton{ dynamic_cast<Button*>(FindGameObject(playButton_)) };
	wassert(pPlayButton && "プレイシーンへ行くボタンがないよ！");

	if (pPlayButton)
	{
		pPlayButton->SetPosition({ playButtonShowPos_.x, static_cast<int>(Mathf::Lerp((screenSize.y * 1.5f) * (1.0f - moveRatio_), static_cast<float>(playButtonShowPos_.y), moveRatio_)) });
		if (pPlayButton->IsPushedFrame())
		{
			System().Get<SceneManager>().Move<PlayScene>();
		}
	}
}

void TitleNeco::Release()
{
}

