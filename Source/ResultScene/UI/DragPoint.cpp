#include "DragPoint.h"

DragPoint::DragPoint(const CoordinateTransformer& _transformer) :
	GameObject{ "Simple.json" },
	centerPosition_{ Vector2Int::Zero() },
	radius_{ 0.0f },
	radiusSq_{ 0.0f },
	isDrag_{ false },
	transformer_{ _transformer }
{
}

DragPoint::~DragPoint()
{
}

void DragPoint::Init()
{
}

void DragPoint::Update()
{
	Cursor& cursor{ System().Get<Cursor>() };
	GameWindow& gameWindow{ System().Get<GameWindow>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	// マウスカーソルの制御
	if (input.IsMouseDown(MouseCode::Left)  // マウス左押された
		&& gameWindow.IsActiveMainWindow()  // かつウィンドウが最前面
		&& gameWindow.IsDefaultControled())  // かつゲーム画面の操作
	{
		Vector2Int cursorPosition{ cursor.GetPosition() };

		Vector2Int offsetPos{ cursorPosition - centerPosition_ };
		int mouseDistanceSq{ offsetPos.x * offsetPos.x + offsetPos.y * offsetPos.y };

		LOGFLN("DragPointdist:{}", std::sqrtf(mouseDistanceSq));

		// マウスへの距離
		if (mouseDistanceSq <= radiusSq_)
		{
			isDrag_ = true;
			dragBegin_ = cursorPosition;
		}
	}

	if (input.IsMouseUp(MouseCode::Left))
	{
		if (isDrag_)
		{
			isDrag_ = false;
		}
	}

	if (isDrag_)
	{
		Vector2Int cursorPosition{ cursor.GetPosition() };
		dragDisplacement_ = cursorPosition - dragBegin_;
	}
}

void DragPoint::Release()
{
}

void DragPoint::SetPosition(const Vector2Int _topLeftPosition)
{
	Vector2Int topLeftPos{ transformer_.ToScreenCoords(_topLeftPosition) };
	Vector2Int halfSize{ transformer_.ToScreenCoords(Vector2{ radius_, radius_ }) };

	centerPosition_ = topLeftPos + halfSize;
}

void DragPoint::SetRadius(const int _radius)
{
	radius_ = static_cast<float>(_radius);
	radiusSq_ = static_cast<float>(_radius * _radius);
}
