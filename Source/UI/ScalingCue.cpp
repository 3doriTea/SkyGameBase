#include "ScalingCue.h"


void ScalingCue::Draw(UI::LayoutConfig* _pLayout, const float _animRatio)
{
	using DirectX::XM_PI;
	float scale{ std::sinf(XM_PI * _animRatio) };

	_pLayout->scale(Vector2{ 30.0f, 30.0f } * scale);
}
