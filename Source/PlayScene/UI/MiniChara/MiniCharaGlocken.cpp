#include "MiniCharaGlocken.h"
#include "../MiniChara.h"


void MiniCharaGlocken::Init(MiniChara& _self)
{
	ResourceSystem& rsrcSystem{ _self.System().Get<ResourceSystem>() };

	_self.hImage_ = rsrcSystem.LoadTexture("Image/MiniChara/Glocken.png");
	wassert((_self.hImage_ != INVALID_HANDLE) && "hImage load feild");

	_self.imageSize_ = rsrcSystem.GetTexture(_self.hImage_)->GetImageSizePix();
	_self.imageSize_ = Vector2Int
	{
		static_cast<int>(_self.imageSize_.x * _self.scale_),
		static_cast<int>(_self.imageSize_.y * _self.scale_),
	};
}

void MiniCharaGlocken::Update(MiniChara& _self)
{
	const Canvas::Context& CONTEXT{ _self.System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};
	config.position(_self.drawPosition_);

	for (float offsetAngle{ 0.0f }; offsetAngle <= 0.5f; offsetAngle += 0.05f)
	{
		float angle{ DirectX::XM_2PI * (_self.animTimeLeft_ / _self.config_.totalAnimTime) + offsetAngle };
		Vector2Int size{ _self.imageSize_ };
		size.x += std::sinf(angle) * 10.0f;
		config.scale(size);
		CONTEXT.SetRefLayout(&config);
		CONTEXT.DrawImage(_self.hImage_);
	}
}
