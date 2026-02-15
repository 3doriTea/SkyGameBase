#include "CoordinateTransformer.h"

wtgb::CoordinateTransformer::CoordinateTransformer(
	const Vector2Int _screenCanvasSize,
	const Vector2Int _designCanvasSize) :
	screenCanvasSize_{ _screenCanvasSize },
	designCanvasSize_{ _designCanvasSize }
{
}

wtgb::CoordinateTransformer::~CoordinateTransformer()
{
}

wtgb::Vector2Int wtgb::CoordinateTransformer::ToScreenCoords(Vector2Int _position) const
{
	// 設計サイズから描画サイズに変換
	const float RATIO_X{ static_cast<float>(screenCanvasSize_.x) / designCanvasSize_.x };
	const float RATIO_Y{ static_cast<float>(screenCanvasSize_.y) / designCanvasSize_.y };

	_position.x = static_cast<int>(_position.x * RATIO_X);
	_position.y = static_cast<int>(_position.y * RATIO_Y);

	return _position;
}

wtgb::Vector2Int wtgb::CoordinateTransformer::ToScreenCoords(Vector2 _position) const
{
	return ToScreenCoords(Vector2Int{ static_cast<int>(_position.x), static_cast<int>(_position.y) });
}
