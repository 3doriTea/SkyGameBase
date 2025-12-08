#pragma once
#include "pch/pch.h"
#include "RenderContent.h"
#include "LayoutConfig.h"

namespace wtgb::UI
{
	using ContentAndConfig = std::tuple<UI::LayoutConfig, UI::RenderContentVT>;
}
