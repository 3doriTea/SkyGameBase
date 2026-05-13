#include "FaderSystem.h"
#include <wtgb.h>

FaderSystem::FaderSystem() :
	hImage_{ INVALID_HANDLE },
	alpha_{ 1.0f },
	fadeType_{ FadeType::FadeOut },
	timeLeft_{ 0.0f },
	maxTimeSec_{ 1.0f }
{
}

FaderSystem::~FaderSystem()
{
}

wtgb::Result FaderSystem::Init(const ViewerInit& _viewer)
{
	//_viewer.Get<ResourceSystem>().LoadTexture()

	return Result::Code::Ok;
}

void FaderSystem::Update(const ViewerUpdate& _system)
{
	if (hImage_ == INVALID_HANDLE)
	{
		return;  // 画像がセットされていなければ表示しない
	}

	const float DT{ _system.Get<GameTime>().GetDeltaTime() };
	ResourceSystem& resource{ _system.Get<ResourceSystem>() };
	const Canvas::Context& CONTEXT{ _system.Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};

	Vector2Int imageSize{ resource.GetTexture(hImage_)->GetImageSizePix() };

	// 原点から描画
	config.position(Vector2Int::Zero());
	Vector2 drawScale{ imageSize };
	drawScale.y *= alpha_;
	config.scale(drawScale);

	// とにかく手前に描画
	config.order(-100);

	CONTEXT.SetRefLayout(&config);
	CONTEXT.DrawImage(hImage_);
	
	// 時間を進める
	if (timeLeft_ > 0.0f)
	{
		timeLeft_ -= DT;
	}

	float alpha{};
	switch (fadeType_)
	{
	case FaderSystem::FadeType::FadeIn:
	{
		// フェードインして隠していく
		if (maxTimeSec_ <= 0.0f)
		{
			alpha = 1.0f;
		}
		else
		{
			alpha = Mathf::Lerp(1.0f, 0.0f, timeLeft_ / maxTimeSec_);
		}
		SetAlpha(alpha);
		break;
	}
	case FaderSystem::FadeType::FadeOut:
	{
		// フェードアウトして表示していく
		if (maxTimeSec_ <= 0.0f)
		{
			alpha = 0.0f;
		}
		else
		{
			alpha = Mathf::Lerp(0.0f, 1.0f, timeLeft_ / maxTimeSec_);
		}
		SetAlpha(alpha);
		break;
	}
	case FaderSystem::FadeType::Stop:
	default:
		// 特に変化なし
		break;
	}
}

void FaderSystem::End()
{
}

void FaderSystem::SetImage(const TextureHandle _hImage)
{
	hImage_ = _hImage;
}

void FaderSystem::In(const float _timeSec)
{
	maxTimeSec_ = _timeSec;
	timeLeft_ = maxTimeSec_;
	fadeType_ = FadeType::FadeIn;
}

void FaderSystem::Out(const float _timeSec)
{
	maxTimeSec_ = _timeSec;
	timeLeft_ = maxTimeSec_;
	fadeType_ = FadeType::FadeOut;
}

void FaderSystem::SetAlpha(const float _alpha)
{
	alpha_ = std::clamp(_alpha, 0.0f, 1.0f);
}
