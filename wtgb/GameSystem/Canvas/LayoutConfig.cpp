#include "pch\pch.h"
#include "LayoutConfig.h"
#include "CanvasContext.h"

wtgb::UI::LayoutConfig::LayoutConfig() :
	pivot_{ Pivot::TopLeft },
	position_{ Vector2::Zero() }
{
}

wtgb::UI::LayoutConfig::~LayoutConfig()
{
}
