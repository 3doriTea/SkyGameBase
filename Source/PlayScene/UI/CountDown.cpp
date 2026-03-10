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

void CountDown::PlayAnimGo(RectF& _rectF)
{
	// ひたすら小さくする
	cellSize_ -= smallingPerFScale_;

	if (cellSize_.x < 0.0f)
	{
		cellSize_ = Vector2Int::Zero();
		DestroyMe();
	}

	_rectF.size = Vector2{ cellSize_ };
}

void CountDown::PlayAnimCountDown(RectF& _rectF)
{
	float animRatio{ std::fmodf(timeLeft_, timeScaleSec_) };
	float moveOffset{ cellSize_.y * std::floorf(timeLeft_ / timeScaleSec_) + cellSize_.y };

	if (animRatio < (moveTimeRatio_ * timeScaleSec_))
	{
		float t{ animRatio / (moveTimeRatio_ * timeScaleSec_) };
		moveOffset += t * cellSize_.y - cellSize_.y;
	}

	_rectF.x = 0.0f;
	_rectF.y = moveOffset;
	_rectF.size = Vector2{ cellSize_ };
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
	smallingPerFScale_ = SafeGet<Vector2Int>(_json, "smallingPerFrameScale");
}

void CountDown::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	timeLeft_ *= timeScaleSec_;
}

void CountDown::Update()
{
	float dt{ System().Get<GameTime>().GetDeltaTime() };

	const Vector2Int SCREEN_SIZE{ System().Get<GameWindow>().GetMainWindowSize() };
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };

	UI::LayoutConfig config{ baseSize_ };
	config
		.position(drawPos_)
		.scale(cellSize_);

	CONTEXT.SetRefLayout(&config);

	RectF drawRectF{};
	if (timeLeft_ > 0.0f)
	{
		timeLeft_ -= dt;
		PlayAnimCountDown(drawRectF);
	}
	else  // カウントダウン終わってGOアニメーション
	{
		timeLeft_ = 0.0f;
		PlayAnimGo(drawRectF);
	}

	CONTEXT.DrawImage(hSlideImage_, 0.0f, drawRectF);
}

void CountDown::Release()
{
}
