#include "MiniCharaMonkitty.h"
#include "../MiniChara.h"

void MiniCharaMonkitty::Init(MiniChara& _self)
{
	ResourceSystem& rsrcSystem{ _self.System().Get<ResourceSystem>() };

	_self.hImage_ = rsrcSystem.LoadTexture("Image/MiniChara/Monkitty.png");
	wassert((_self.hImage_ != INVALID_HANDLE) && "hImage load feild");

	_self.imageSize_ = rsrcSystem.GetTexture(_self.hImage_)->GetImageSizePix();
	_self.imageSize_ = Vector2Int
	{
		static_cast<int>(_self.imageSize_.x * _self.scale_.x),
		static_cast<int>(_self.imageSize_.y * _self.scale_.y),
	};
}

void MiniCharaMonkitty::Update(MiniChara& _self)
{
	const Canvas::Context& CONTEXT{ _self.System().Get<Canvas>().GetContext() };
	
	UI::LayoutConfig config{};
	config.positionPivot(UI::Pivot::Center);
	config.position(_self.drawPosition_);

	float angle{ DirectX::XM_2PI * (_self.animTimeLeft_ / _self.config_.totalAnimTime) };
	Vector2Int size{ _self.imageSize_ };
	size.x += static_cast<int>(std::sinf(angle) * 10.0f);
	config.scale(size);
	CONTEXT.SetRefLayout(&config);
	CONTEXT.DrawImage(_self.hImage_, angle);
}
