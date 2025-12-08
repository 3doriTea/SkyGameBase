#include "pch\pch.h"  
#include "../Canvas.h"  

void wtgb::UI::CanvasContext::SetLayout(const LayoutConfig& _config)  
{  
   currentConfig_ = _config;  
}  

void wtgb::UI::CanvasContext::DrawBox(const Color _color, const float _angle)  
{
	AddRenderOrder(RenderContentBox{ _color, _angle });
}

void wtgb::UI::CanvasContext::DrawBox(const Color _color, const float _angle)  
{
	AddRenderOrder(RenderContent<RenderContentType::Image>{ _color, _angle });
}

void wtgb::UI::CanvasContext::AddRenderOrder(const RenderContentVT& _content)  
{  
   GetAccess()->renderOrder_.push_back({ currentConfig_, _content });  
}
