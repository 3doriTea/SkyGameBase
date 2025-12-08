#pragma once
#include "pch/pch.h"
#include "Pivot.h"

#define LAYOUT_BUILDER_SETTER_PARAM(TYPE, UNIT_NAME)\
	LayoutConfig& UNIT_NAME(const TYPE& _##UNIT_NAME) { UNIT_NAME##_ = _##UNIT_NAME; return *this; }

namespace wtgb::UI
{
	/// <summary>
	/// 配置の設定
	/// </summary>
	class LayoutConfig
	{
		friend class CanvasContext;
	public:
		LayoutConfig();
		~LayoutConfig();

		/// <summary>
		/// 指定座標の基準点
		/// </summary>
		LAYOUT_BUILDER_SETTER_PARAM(Pivot, positionPivot)
		/// <summary>
		/// 矩形の基準点座標
		/// </summary>
		LAYOUT_BUILDER_SETTER_PARAM(Vector2, position)
		/// <summary>
		/// 矩形の基準点からの大きさ
		/// </summary>
		LAYOUT_BUILDER_SETTER_PARAM(Vector2, scale)

		/// <summary>
		/// スクリーンサイズから矩形の行列を取得する
		/// </summary>
		Matrix4x4 GetProjectionMatrix(const Vector2Int _screenSize) const;

	private:
		Pivot positionPivot_;  // 矩形の始点は画面のどこ基準か
		Vector2 position_;     // 矩形の始点
		Vector2 scale_;        // 矩形の大きさ
	};
}
