#include "Orb.h"

Orb::Orb(const Vector2Int _position, const Vector2Int _target, const float _time, const OrbType _type) :
	GameObject{ "Play/UI/Orb.json" },
	type_{ _type },
	position_{ _position }
{
	velocity_ = Vector2{ _target - _position } / _time;
}

Orb::~Orb()
{}

void Orb::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
	scalingTimeLeft_ = scalingTime_;

	ResourceSystem& rsrcSystem{ System().Get<ResourceSystem>() };

	hImage_ = rsrcSystem.LoadTexture(imageFilePath_);
	wassert((hImage_ != INVALID_HANDLE) && "hImage load feild");

	imageSize_ = rsrcSystem.GetTexture(hImage_)->GetImageSizePix();
	offset_ = imageSize_ / 2.0f;
}

void Orb::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	if (scalingTimeLeft_ > 0.0f)
	{
		scalingTimeLeft_ -= DT;
		if (scalingTimeLeft_ <= 0.0f)
		{
			scalingTimeLeft_ = 0.0f;  // 0に揃える
		}
	}

	// 速度適用移動する
	position_ = position_ + velocity_ * DT;

	// 描画
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};
	CONTEXT.SetRefLayout(&config);
	config.position(position_ - offset_);
	config.scale(Mathf::Lerp(imageSize_, Vector2::Zero(), scalingTimeLeft_ / scalingTime_));

	if (position_.y < offset_.y)
	{
		// 画面範囲外なら消す
		DestroyMe();
	}

	CONTEXT.DrawImage(hImage_);
}

void Orb::Release()
{}

void Orb::OnLoadParam(const json& _json)
{
	_json["imageFilesPath"][static_cast<size_t>(type_)].get_to(imageFilePath_);
	scalingTime_ = SafeGet<float>(_json, "scalingTime");
}
