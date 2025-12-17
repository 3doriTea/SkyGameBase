#include "pch/pch.h"
#include "TitleNeco.h"

TitleNeco::TitleNeco() :
	GameObject{ "Simple.json" },
	hImages_{}
{
}

TitleNeco::~TitleNeco()
{
}

void TitleNeco::Init()
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };

	fs::path dir{ "./Image/Title" };

	hImages_[I_HAND] = rc.LoadTexture(dir / "TitleNeco-Hand.png");
	hImages_[I_HANG] = rc.LoadTexture(dir / "TitleNeco-Hang.png");
	hImages_[I_NORM] = rc.LoadTexture(dir / "TitleNeco-Norm.png");
}

void TitleNeco::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };

	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	const Vector2Int screenSizeInt{ System().Get<GameWindow>().GetMainWindowSize() };
	const Vector2 screenSize{ static_cast<float>(screenSizeInt.x), static_cast<float>(screenSizeInt.y) };

	UI::LayoutConfig config{ UI::LayoutConfig{}.position({ 0, 0 }).scale(screenSize) };
	context.SetRefLayout(&config);

	if (input.IsMouseDown(MouseCode::Left))
	{
		cursor.SetShow(false);
		cursor.SetLock(true, cursor.GetPosition());
		isDrag_ = true;
	}
	if (input.IsMouseUp(MouseCode::Left))
	{
		cursor.SetShow(true);
		cursor.SetLock(false, {});
		isDrag_ = false;
	}

	if (isDrag_)
	{
		Vector2Int move{ cursor.GetFrameMove() };
		moveRatio_ -= static_cast<float>(move.y) / screenSize.y;
		moveRatio_ = min(max(moveRatio_, 0.0f), 1.0f);
	}
	else
	{
		moveRatio_ = 0.0f;
	}

	config.position({ 0, screenSize.y * (1.0f - moveRatio_) + screenSize.y });
	context.DrawImage(hImages_[I_NORM]);

	config.position({ 0, (screenSize.y / 2.0f) * (1.0f - moveRatio_) + (screenSize.y / 2.0f) });
	context.DrawImage(hImages_[I_HAND]);
}

void TitleNeco::Release()
{
}
