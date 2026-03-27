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
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

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

		LOGFLN("DragCircleDist:{}", std::sqrtf((float)mouseDistanceSq));

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
		
		dragDifference_ = Vector2Int::Zero();
		dragDisplacementPrev_ = Vector2Int::Zero();
	}

	if (input.IsMouseUp(MouseCode::Left))
	{
		if (isDrag_)
		{
			isDrag_ = false;
			onOut_();
		}
	}

	Vector2Int cursorPosition{ cursor.GetPosition() };
	if (isDrag_)
	{
		float vv = std::powf(0.1f, DT);

		dragDisplacement_ = cursorPosition - dragBegin_;
		velocityY_ = Mathf::Lerp(
			velocityY_,
			dragDisplacementPrev_.y - dragDisplacement_.y,
			vv);
	}
	else
	{
		//dragDisplacementPrev_.y = dragDisplacement_.y - velocityY_;
		//dragDisplacement_.y = ;
		if (velocityY_ > 0.0f)
		{
			//velocityY_ -= 0.000001f;
		}
		dragBegin_ = cursorPosition;
	}
	//LOGFLN("velocityY_:{:.6}", velocityY_);

	dragDifference_ = dragDisplacement_ - dragDisplacementPrev_;
	dragDisplacementPrev_ = dragDisplacement_;

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
