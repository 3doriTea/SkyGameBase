#include "pch\pch.h"
#include "CanvasContext.h"
#include "LayoutConfig.h"

void wtgb::UI::CanvasContext::SetLayout(const LayoutConfig& _config)
{
	currentConfig_ = _config;
}

void wtgb::UI::CanvasContext::DrawImage(const TextureHandle _hTexture)
{
	
}

void wtgb::UI::CanvasContext::AddRenderOrder(const RenderContentVT& _content)
{
	renderOrder_.push_back({ currentConfig_, _content });
}
