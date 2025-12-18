#include "pch/pch.h"
#include "TitleNeco.h"
#include "../SMF/SMFPlayer.h"
#include "../UI/DragCircle.h"

TitleNeco::TitleNeco(const EntityId _dragCircle) :
	GameObject{ "Simple.json" },
	hImages_{},
	isDrag_{ false },
	moveRatio_{},
	dragCircle_{ _dragCircle }
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

	Vector2Int centerPosition
	{
		(560 / 1920.0f) * screenSize.x, screenSize.y / 2.0f,
	};

	//dragCircle_ = GetScene<SampleScene>().Instantiate<DragCircle>(centerPosition, 30);
	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };

	pDragCircle->SetPosition(centerPosition);
	pDragCircle->SetRadius(30);

	fs::path dir{ "./Image/Title" };

	hImages_[I_HAND] = rc.LoadTexture(dir / "TitleNeco-Hand.png");
	hImages_[I_HANG] = rc.LoadTexture(dir / "TitleNeco-Hang.png");
	hImages_[I_NORM] = rc.LoadTexture(dir / "TitleNeco-Norm.png");

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject("SMFPlayer")) };
	if (pSMFPlayer)
	{  // SMFPlayer‚ª‚¢‚é‚È‚çÄ¶
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

	SMFPlayer* pSMFPlayer{ dynamic_cast<SMFPlayer*>(FindGameObject("SMFPlayer")) };

	if (pSMFPlayer)  // SMFPlayer‚ªŒ©‚Â‚©‚Á‚½‚È‚ç
	{
		pSMFPlayer->OnNote([pSMFPlayer](Note _note)
			{
				if (_note.channel == 0x03)
				{
					_note.noteNumber -= 12 * 2;
					pSMFPlayer->PlayTone(_note);
				}
			});
	}

	DragCircle* pDragCircle{ dynamic_cast<DragCircle*>(FindGameObject(dragCircle_)) };

	if (pDragCircle && pDragCircle->IsDrag())
	{
		Vector2Int displacement{ pDragCircle->GetDisplacement() };
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


	UI::LayoutConfig config{};
	context.SetRefLayout(&config);

	#if 0
	{
		RectF handArea
		{
			(560 / 1920.0f) * screenSize.x, screenSize.y / 2,
			(153 / 1920.0f) * screenSize.x, screenSize.y / 2,
		};
		if (input.IsMouseDown(MouseCode::Left))
		{
			Vector2Int clickPos{ cursor.GetPosition() };
			if (handArea.GetBegin().x < clickPos.x && clickPos.x < handArea.GetEnd().x
			 && handArea.GetBegin().y < clickPos.y && clickPos.y < handArea.GetEnd().y)
			{
				cursor.SetShow(false);
				//cursor.SetLock(true, clickPos);
				isDrag_ = true;
			}
		}
		if (input.IsMouseUp(MouseCode::Left))
		{
			cursor.SetShow(true);
			//cursor.SetLock(false, {});
			isDrag_ = false;
		}

		if (isDrag_)
		{
			Vector2Int move{ cursor.GetFrameMove() };
			moveRatio_ -= static_cast<float>(move.y) / screenSize.y;
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
	}
	#endif

	TextureHandle hBodyImage
	{
		isDrag_
		? hImages_[I_HANG]
		: hImages_[I_NORM]
	};

	config.scale({ screenSize.x, screenSize.y });
	config.position({ 0, screenSize.y * (1.0f - moveRatio_) });
	context.DrawImage(hBodyImage);

	config.position({ 0, (screenSize.y / 2.0f) * (1.0f - moveRatio_) });
	context.DrawImage(hImages_[I_HAND]);
}

void TitleNeco::Release()
{
}
