#pragma once
#include "pch/pch.h"
#include "Pivot.h"

#define LAYOUT_BUILDER_SETTER_PARAM(TYPE, UNIT_NAME)\
	LayoutConfig& UNIT_NAME(const TYPE& _##UNIT_NAME) { UNIT_NAME##_ = _##UNIT_NAME; return *this; }

namespace wtgb::UI
{
	class LayoutConfig
	{
		friend CanvasContext;
	public:
		LayoutConfig();
		~LayoutConfig();

		/// <summary>
		/// 指定座標の基準点
		/// </summary>
		LAYOUT_BUILDER_SETTER_PARAM(Pivot, pivot)
		/// <summary>
		/// 基準点に影響される座標
		/// </summary>
		LAYOUT_BUILDER_SETTER_PARAM(Vector2, position)

	private:
		Pivot pivot_;
		Vector2 position_;
	};
}
