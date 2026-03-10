#include "pch\pch.h"
#include "DragCircle.h"

DragCircle::DragCircle() :
	DragCircle{ Vector2Int::Zero(), 0 }
{
}

DragCircle::DragCircle(const Vector2Int _centerPosition, const int _radius, const Vector2Int _baseCanvasSize) :
	GameObject{ "Simple.json" },
	hCircleImage_{ INVALID_HANDLE },
	isDrag_{ false },
	centerPosition_{ _centerPosition },
	dragBegin_{ Vector2Int::Zero() },
	dragDisplacement_{ Vector2Int::Zero() },
	radius_{ _radius },
	radiusSq_{ _radius * _radius },
	baseCanvasSize_{ _baseCanvasSize },

	onClickInRadius_{ []{} },
	onClickOutRadius_{ []{} },
	onOut_{ []{} }
{
}

DragCircle::~DragCircle()
{
}

void DragCircle::Init()
{
	ResourceSystem& resource{ System().Get<ResourceSystem>() };

	hCircleImage_ = resource.LoadTexture("Image/MouseCircle.png");
}

void DragCircle::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };
	GameWindow& gameWindow{ System().Get<GameWindow>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };

	UI::LayoutConfig config{ baseCanvasSize_ };
	context.SetRefLayout(&config);

	// マウスカーソルの制御
	if (input.IsMouseDown(MouseCode::Left)  // マウス左押された
		&& gameWindow.IsActiveMainWindow()  // かつウィンドウが最前面
		&& gameWindow.IsDefaultControled())  // かつゲーム画面の操作
	{
		Vector2Int cursorPosition{ cursor.GetPosition() };
		
		Vector2Int offsetPos{ cursorPosition - centerPosition_ };
		int mouseDistanceSq{ offsetPos.x * offsetPos.x + offsetPos.y * offsetPos.y };

		LOGFLN("DragCircleDist:{}", std::sqrtf(mouseDistanceSq));

		if (mouseDistanceSq <= radiusSq_)
		{
			isDrag_ = true;
			onClickInRadius_();
			dragBegin_ = cursorPosition;
		}
		else
		{
			onClickOutRadius_();
		}
		
	}

	if (input.IsMouseUp(MouseCode::Left))
	{
		if (isDrag_)
		{
			isDrag_ = false;
			onOut_();
		}
	}

	if (isDrag_)
	{
		Vector2Int cursorPosition{ cursor.GetPosition() };
		dragDisplacement_ = cursorPosition - dragBegin_;
	}

	config.position(Vector2{ centerPosition_ } - Vector2::One() * static_cast<float>(radius_));
	config.scale(Vector2::One() * (radius_ * 2.0f));

	context.DrawImage(hCircleImage_);
}

void DragCircle::Release()
{
}

void DragCircle::SetRadius(const int _radius)
{
	radius_ = _radius;
	radiusSq_ = _radius * _radius;
}
