#include "MiniCharaBase3.h"
#include "../MiniChara.h"

void MiniCharaBase3::Init(MiniChara& _self)
{
	ResourceSystem& rsrcSystem{ _self.System().Get<ResourceSystem>() };

	_self.hImage_ = rsrcSystem.LoadTexture("Image/MiniChara/Base3.png");
	wassert((_self.hImage_ != INVALID_HANDLE) && "hImage load feild");

	_self.imageSize_ = rsrcSystem.GetTexture(_self.hImage_)->GetImageSizePix();
	_self.imageSize_ = Vector2Int
	{
		static_cast<int>(_self.imageSize_.x * _self.scale_.x),
		static_cast<int>(_self.imageSize_.y * _self.scale_.y),
	};
}

void MiniCharaBase3::Update(MiniChara& _self)
{
	const Canvas::Context& CONTEXT{ _self.System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};
	config.position(_self.drawPosition_);

	for (float offsetAngle{ 0.0f }; offsetAngle <= 0.5f; offsetAngle += 0.05f)
	{
		float angle{ DirectX::XM_2PI * (_self.animTimeLeft_ / _self.config_.totalAnimTime) + offsetAngle };
		Vector2Int size{ _self.imageSize_ };
		size.x += static_cast<int>(std::sinf(angle) * 10.0f);
		config.scale(size);
		CONTEXT.SetRefLayout(&config);
		CONTEXT.DrawImage(_self.hImage_);
	}
}
