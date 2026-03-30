#include "PerfectTimer.h"
#include "CoreType/ExtJson/Color.h"

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
	OnLoadParam(GetComponent<Parameter>().Load());
}

void PerfectTimer::Update()
{
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };

	UI::LayoutConfig config{};
	CONTEXT.SetRefLayout(&config);

#pragma region ゲージの縁
	config
		.position(Vector2Int{ 0, SCREEN_SIZE.y - height_ })
		.scale(SCREEN_SIZE);
	CONTEXT.DrawBox(bar_.thicknessColor);
#pragma endregion

#pragma region ゲージの背景
	config
		.position(Vector2Int{ 0, SCREEN_SIZE.y - height_ + margin_ })
		.scale(SCREEN_SIZE);
	CONTEXT.DrawBox(bar_.backColor);
#pragma endregion

#pragma region ゲージを塗っていく
	Color fillColor{ ratio_ < 1.0f ? bar_.fillColorNormal : bar_.fillColorFull };
	
	float leftX{ Mathf::Lerp(0.0f, SCREEN_SIZE.x * 0.5f, ratio_) };

	config
		.position(Vector2{ 0.0f, static_cast<float>(SCREEN_SIZE.y - height_ + margin_) })
		.scale(Vector2{ leftX, static_cast<float>(SCREEN_SIZE.y) });
	CONTEXT.DrawBox(fillColor);

	//float leftX{ Mathf::Lerp(0.0f, SCREEN_SIZE.x * 0.5f, ratio_) };
	config
		.position(Vector2{ SCREEN_SIZE.x - SCREEN_SIZE.x * 0.5f * ratio_, static_cast<float>(SCREEN_SIZE.y - height_ + margin_) })
		.scale({ (SCREEN_SIZE.x * 0.5f) * ratio_, static_cast<float>(SCREEN_SIZE.y) });
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

void PerfectTimer::OnLoadParam(const json& _json)
{
	height_ = SafeGet<int>(_json, "height");
	margin_ = SafeGet<int>(_json, "margin");

	bar_.backColor = SafeGet<Color>(_json, "barBackColor");
	bar_.thicknessColor = SafeGet<Color>(_json, "barThicknessColor");
	bar_.fillColorNormal = SafeGet<Color>(_json, "barFillColorNormal");
	bar_.fillColorFull = SafeGet<Color>(_json, "barFillColorFull");
}
