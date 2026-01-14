#include "CountDown.h"

CountDown::CountDown() :
	GameObject{ "CountDown.json" },
	timeLeft_{ 0.0f },
	hSlideImage_{ INVALID_HANDLE },
	cellSize_{}
{
}

CountDown::~CountDown()
{
}

void CountDown::OnLoadParam(const json& _json)
{
	
}

void CountDown::Init()
{
}

void CountDown::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };

	if (timeLeft_ > 0.0f)
	{
		timeLeft_ -= dt;
	}
	else
	{
		timeLeft_ = 0.0f;
		DestroyMe();
	}

	UI::LayoutConfig config{};
	config
		.position(position_)
		.scale(size_);

	context.SetRefLayout(&config);
	context.DrawImage(hImage);
}
