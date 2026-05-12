#include "FaderSystem.h"
#include <wtgb.h>

FaderSystem::FaderSystem() :
	hImage_{ INVALID_HANDLE }
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

	ResourceSystem& resource{ _system.Get<ResourceSystem>() };
	const Canvas::Context& CONTEXT{ _system.Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};

	Vector2Int imageSize{ resource.GetTexture(hImage_)->GetImageSizePix() };

	// 原点から描画
	config.position(Vector2Int::Zero());
	config.scale(imageSize);

	// とにかく手前に描画
	config.order(-100);

	for (float offsetAngle{ 0.0f }; offsetAngle <= 0.5f; offsetAngle += 0.05f)
	{
		CONTEXT.SetRefLayout(&config);
		CONTEXT.DrawImage(hImage_);
	}
}

void FaderSystem::End()
{
}

void FaderSystem::SetImage(const TextureHandle _hImage)
{
	hImage_ = _hImage;
}
