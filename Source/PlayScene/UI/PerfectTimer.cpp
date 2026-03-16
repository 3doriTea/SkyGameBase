#include "PerfectTimer.h"

PerfectTimer::PerfectTimer() :
	GameObject{ "Play/UI/PerfectTimer.json" },
	ratio_{}
{
}

PerfectTimer::~PerfectTimer()
{
}

void PerfectTimer::Init()
{
	OnLoad(GetComponent<Parameter>().Load());
}

void PerfectTimer::Update()
{
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };


	UI::LayoutConfig config{};
	CONTEXT.SetRefLayout(&config);

#pragma region ゲージの縁
	config
		.position(Vector2Int::Zero())
		.scale({ static_cast<float>(SCREEN_SIZE.x), height_ });
	CONTEXT.DrawBox(bar_.thicknessColor);
#pragma endregion

#pragma region ゲージの背景
	config
		.position(Vector2Int::Zero())
		.scale({ static_cast<float>(SCREEN_SIZE.x), height_ - margin_ });
	CONTEXT.DrawBox(bar_.backColor);
#pragma endregion

#pragma region ゲージを塗っていく
	Color fillColor{ ratio_ < 1.0f ? bar_.fillColorNormal : bar_.fillColorFull };
	
	config
		.position(Vector2Int::Zero())
		.scale({ (SCREEN_SIZE.x * 0.5f) * ratio_, height_ - margin_ });
	CONTEXT.DrawBox(fillColor);

	config
		.position({ SCREEN_SIZE.x - SCREEN_SIZE.x * 0.5f * ratio_, 0.0f })
		.scale({ (SCREEN_SIZE.x * 0.5f) * ratio_, height_ - margin_ });
	CONTEXT.DrawBox(fillColor);
#pragma endregion
}

void PerfectTimer::Release()
{
}

void PerfectTimer::SetRatio(const float _ratio)
{
	ratio_ = _ratio;
}

void PerfectTimer::OnLoad(const json& _json)
{
	height_ = SafeGet<float>(_json, "height");
	margin_ = SafeGet<float>(_json, "margin");

	bar_.backColor = SafeGet<Color>(_json, "barBackColor");
	bar_.thicknessColor = SafeGet<Color>(_json, "barThicknessColor");
	bar_.fillColorNormal = SafeGet<Color>(_json, "barFillColorNormal");
	bar_.fillColorFull = SafeGet<Color>(_json, "barFillColorFull");
}
