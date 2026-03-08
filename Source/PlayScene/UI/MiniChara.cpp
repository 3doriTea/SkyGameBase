#include "MiniChara.h"
#include "SMF/SMFPlayer.h"


MiniChara::MiniChara(const EntityId _dropCloud, const EntityId _smfPlayer) :
	GameObject{ "Play/UI/MiniChara.json" },
	dropCloud_{ _dropCloud },
	hImage_{ INVALID_HANDLE },
	imageSize_{ Vector2Int::Zero() },
	animTimeLeft_{},
	smfPlayer_{ _smfPlayer },
	scale_{ 0.5f }
{
}

MiniChara::~MiniChara()
{
}

void MiniChara::OnLoadParam(const json& _json)
{
}

void MiniChara::Init()
{
	//OnLoadParam(GetComponent<Parameter>().Load());

	ResourceSystem& rsrcSystem{ System().Get<ResourceSystem>() };

	hImage_ = rsrcSystem.LoadTexture("Image/MiniChara/Base3.png");
	wassert((hImage_ != INVALID_HANDLE) && "hImage load feild");

	imageSize_ = rsrcSystem.GetTexture(hImage_)->GetImageSizePix();
	imageSize_ = Vector2Int
	{
		static_cast<int>(imageSize_.x * scale_),
		static_cast<int>(imageSize_.y * scale_),
	};

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	if (pSMFPlayer)
	{
		totalAnimTime_ = pSMFPlayer->GetQuarterSec();
	}
	assert(totalAnimTime_ > 0 && "feild to get total anim time");
}

void MiniChara::Update()
{
	const Canvas::Context& CONTEXT{ System().Get<Canvas>().GetContext() };
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	
	animTimeLeft_ -= DT;
	if (animTimeLeft_ <= 0.0f)
	{
		animTimeLeft_ += totalAnimTime_;
	}

	UI::LayoutConfig config{};
	config.position(Vector2Int::Zero());

	for (float offsetAngle{ 0.0f }; offsetAngle <= 0.5f; offsetAngle += 0.05f)
	{
		float angle{ DirectX::XM_2PI * (animTimeLeft_ / totalAnimTime_) + offsetAngle };
		Vector2Int size{ imageSize_ };
		size.x += std::sinf(angle) * 10.0f;
		config.scale(size);
		CONTEXT.SetRefLayout(&config);
		CONTEXT.DrawImage(hImage_);
	}
}
