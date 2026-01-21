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

	UI::LayoutConfig config{ baseSize_ };
	config
		.position(drawPos_)
		.scale(cellSize_);

	CONTEXT.SetRefLayout(&config);

	#if 1
	if (timeLeft_ > 0.0f)
	{
		timeLeft_ -= dt;
	}
	else
	{
		timeLeft_ = 0.0f;
		DestroyMe();
	}

	int cellIndex{ static_cast<int>(timeLeft_) };

	float animRatio{ std::fmodf(timeLeft_, 1.0f) };
	float moveOffset{ 0.0f };

	if (animRatio < moveTimeRatio_)
	{
		float t{ (animRatio / moveTimeRatio_) };
		moveOffset = t * cellSize_.y;
	}

	float posV{ static_cast<float>(cellSize_.y) * cellIndex + moveOffset };

	Vector2 cellBeginPos{ 0.0f, posV, };
	Vector2 cellSizeF{ cellSize_ };
	#else
	static Vector2 cellBeginPos{ 0.0f, 0.0f, };
	static Vector2 cellSizeF{ cellSize_ };
	ImGui::Begin("Cell");
	ImGui::DragFloat("beginX", &cellBeginPos.x);
	ImGui::DragFloat("beginY", &cellBeginPos.y);
	ImGui::DragFloat("sizeX", &cellSizeF.x);
	ImGui::DragFloat("sizeY", &cellSizeF.y);
	ImGui::End();

	#endif
	
	CONTEXT.DrawImage(hSlideImage_, 0.0f, RectF{ cellBeginPos, cellSizeF });
}

void CountDown::Release()
{
}
