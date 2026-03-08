#include "MiniChara.h"
#include "SMF/SMFPlayer.h"
#include "MiniChara/MiniCharaMonkitty.h"
#include "MiniChara/MiniCharaBase3.h"


MiniChara::MiniChara(
	const EntityId _dropCloud,
	const EntityId _smfPlayer,
	const MiniCharaType _type) :
	GameObject{ "Play/UI/MiniChara.json" },
	dropCloud_{ _dropCloud },
	hImage_{ INVALID_HANDLE },
	imageSize_{ Vector2Int::Zero() },
	animTimeLeft_{},
	smfPlayer_{ _smfPlayer },
	scale_{ 0.5f },
	pMiniCharaState_{},
	totalAnimTime_{}
{
	switch (_type)
	{
		case MiniCharaType::Monkitty:
			pMiniCharaState_ = std::make_unique<MiniCharaMonkitty>();
			break;
		case MiniCharaType::Base3:
			pMiniCharaState_ = std::make_unique<MiniCharaBase3>();
			break;
		default:
			wassert(false && "unknown type of mini chara");
			break;
	}
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

	SMFPlayer* pSMFPlayer{ FindGameObject<SMFPlayer>(smfPlayer_) };
	if (pSMFPlayer)
	{
		totalAnimTime_ = pSMFPlayer->GetQuarterSec();
	}
	assert(totalAnimTime_ > 0 && "feild to get total anim time");

	pMiniCharaState_.get()->Init(*this);
}

void MiniChara::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };
	
	animTimeLeft_ -= DT;
	if (animTimeLeft_ <= 0.0f)
	{
		animTimeLeft_ += totalAnimTime_;
	}

	pMiniCharaState_.get()->Update(*this);
}
