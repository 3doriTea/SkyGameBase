#include "pch\pch.h"
#include "../Canvas.h"

void wtgb::UI::CanvasContext::SetLayout(const LayoutConfig& _config)
{
	currentConfig_ = _config;
}

void wtgb::UI::CanvasContext::DrawImage(const TextureHandle _hTexture, const float _angle)
{
	AddRenderOrder(RenderContent<RenderContentType::Image>{ _hTexture, _angle });
}

void wtgb::UI::CanvasContext::DrawBox(const Color _color, const float _angle)
{
	AddRenderOrder(RenderContent<RenderContentType::Box>{ _color, _angle });
}

void wtgb::UI::CanvasContext::AddRenderOrder(const RenderContentVT& _content)
{
	GetAccess()->renderOrder_.push_back({ currentConfig_, _content });
}
