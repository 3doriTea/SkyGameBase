#include "pch\pch.h"
#include "LayoutConfig.h"
#include "CanvasContext.h"

wtgb::UI::LayoutConfig::LayoutConfig() :
	positionPivot_{ Pivot::TopLeft },
	position_{ Vector2::Zero() },
	scale_{ Vector2::Zero() }
{
}

wtgb::UI::LayoutConfig::~LayoutConfig()
{
}

wtgb::Matrix4x4 wtgb::UI::LayoutConfig::GetProjectionMatrix(const Vector2Int _screenSize) const
{
	using namespace DirectX;

	// 数学座標と描画座標のy軸差異解消
	RectF cartesianBox{ position_, scale_ };
	cartesianBox.y = _screenSize.y - cartesianBox.y;
	cartesianBox.height *= -1;

	const Vector2 VIEW_BEGIN{ cartesianBox.GetBegin() };
	const Vector2 VIEW_END{ cartesianBox.GetEnd() };

	// 表示するサイズに合わせる
	Matrix4x4 scalingBox = XMMatrixScaling(
		std::abs(VIEW_END.x - VIEW_BEGIN.x) * 2.0f,
		std::abs(VIEW_END.y - VIEW_BEGIN.y) * 2.0f,
		1.0f);

	// 表示するボックスの位置を移動する
	Matrix4x4 moveBox = XMMatrixTranslation(
		((VIEW_END.x - VIEW_BEGIN.x) / 2.0f + VIEW_BEGIN.x) / (_screenSize.x / 2.0f),
		((VIEW_BEGIN.y - VIEW_END.y) / 2.0f + VIEW_END.y) / (_screenSize.y / 2.0f),
		0.0f);

	// 画面に合わせる
	Matrix4x4 scalingView = XMMatrixScaling(
		1.0f / (_screenSize.x * 2),
		1.0f / (_screenSize.y * 2),
		1.0f);

	// オフセット - 画面中心は(0, 0) 左下は(-1, -1)
	Matrix4x4 offsetView
	{
		XMMatrixTranslation(-1.0f, -1.0f, 0.0f)
	};

	// 最終的な行列
	Matrix4x4 world
	{
		scalingBox * scalingView * moveBox * offsetView
	};

	// 矩形移動行列
	Matrix4x4 matrixProjection{ XMMatrixTranspose(world) };

	return matrixProjection;
}
