#include "Orb.h"

Orb::Orb(const Vector2Int _position, const Vector2Int _target, const float _time, const OrbType _type) :
	GameObject{ "Play/UI/Orb.json" },
	type_{ _type }
{}

Orb::~Orb()
{}

void Orb::Init()
{
	OnLoad(GetComponent<Parameter>().Load());
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
	position_ = position_ + velocity_;

	// 描画
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	UI::LayoutConfig config{};
	config.position(position_ - offset_);
	config.scale(Mathf::Lerp(imageSize_, Vector2::Zero(), scalingTimeLeft_ / scalingTime_));

	if (position_.y < offset_.y)
	{
		// 画面範囲外なら消す
		DestroyMe();
	}
}

void Orb::Release()
{}

void Orb::OnLoad(const json& _json)
{
	std::string dummm{ _json.dump() };
	bool isarrrrr = _json["imageFilesPath"].is_array();
	_json["imageFilesPath"].array().at(0);


	_json["imageFilesPath"].array()[0].get_to(imageFilePath_);
	scalingTime_ = SafeGet<float>(_json, "scalingTime");
}
