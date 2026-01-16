#include "CountDown.h"

CountDown::CountDown() :
	GameObject{ "CountDown.json" },
	timeLeft_{ 0.0f },
	hSlideImage_{ INVALID_HANDLE },
	cellSize_{},
	imageSize_{}
{
}

CountDown::~CountDown()
{
}

void CountDown::OnLoadParam(const json& _json)
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };

	baseSize_ = SafeGet<Vector2Int>(_json, "baseSize");
	cellSize_ = SafeGet<Vector2Int>(_json, "cellSize");
	imageSize_ = SafeGet<Vector2Int>(_json, "imageSize");
	drawPos_ = SafeGet<Vector2Int>(_json, "drawPos");

	std::string filePath{ _json["slideImageFile"].get<std::string>() };
	hSlideImage_ = rc.LoadTexture(filePath);

	timeLeft_ = SafeGet<float>(_json, "countDownTime");
	timeScaleSec_ = SafeGet<float>(_json, "countDownTimeScale");
	moveTimeRatio_ = SafeGet<float>(_json, "countDownMoveRatio");
}

void CountDown::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void CountDown::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };
	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };

	if (timeLeft_ > 0.0f)
	{
		timeLeft_ -= dt;
	}
	else
	{
		timeLeft_ = 0.0f;
		DestroyMe();
	}

	UI::LayoutConfig config{ baseSize_ };
	config
		.position(drawPos_)
		.scale(cellSize_);

	CONTEXT.SetRefLayout(&config);

	int cellIndex{ static_cast<int>(timeLeft_ / timeScaleSec_) };

	float totalAnimRatio{ std::fmodf(timeLeft_, timeScaleSec_) / timeScaleSec_ };
	float moveAnimRatio{};

	if (totalAnimRatio < moveTimeRatio_)
	{
		moveAnimRatio = totalAnimRatio / moveTimeRatio_;
	}
	else
	{
		moveAnimRatio = 1.0f;
	}

	Vector2 cellBeginPos
	{
		0.0f,
		moveAnimRatio * cellSize_.y + cellIndex * cellSize_.y
	};

	Vector2 cellSizeF{ cellSize_ };
	
	CONTEXT.DrawImage(hSlideImage_, 0.0f, RectF{ cellBeginPos, cellSizeF });
}

void CountDown::Release()
{
}
