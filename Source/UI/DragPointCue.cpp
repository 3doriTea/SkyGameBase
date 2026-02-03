#include "DragPointCue.h"

DragPointCue::DragPointCue(
	const std::string& _imageFilePath,
	const float _animTotalTimeSec,
	const Vector2Int _drawPosition,
	const Vector2Int _drawSize,
	const Vector2Int _baseCanvasSize) :
	GameObject{ "Simple.json" },
	timeLeft_{ 0.0f },
	animTotalTimeSec_{ _animTotalTimeSec },
	baseCanvasSize_{ _baseCanvasSize },
	drawPosition_{ _drawPosition },
	drawSize_{ _drawSize },
	imageFilePath_{},
	hImage_{ INVALID_HANDLE }
{
}

DragPointCue::DragPointCue(const std::string& _imageFilePath, const float _animTotalTimeSec) :
	DragPointCue
	{
		_imageFilePath,
		_animTotalTimeSec,
		Vector2Int::Zero(),
		Vector2Int::Zero(),
		Vector2Int::Zero()
	}
{
}

DragPointCue::~DragPointCue()
{
}

void DragPointCue::Init()
{
	ResourceSystem& resource{ System().Get<ResourceSystem>() };

	hImage_ = resource.LoadTexture(imageFilePath_);
}

void DragPointCue::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	timeLeft_ -= DT;

	if (timeLeft_ <= 0.0f)
	{
		timeLeft_ += animTotalTimeSec_;
	}

	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{ baseCanvasSize_ };
	context.SetRefLayout(&config);

	config.position(drawPosition_);
	config.scale(drawSize_);

	context.DrawImage(hImage_);
}

void DragPointCue::Release()
{
}
