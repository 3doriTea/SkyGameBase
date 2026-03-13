#include "MiniChara.h"
#include "SMF/SMFPlayer.h"
#include "MiniChara/MiniCharaBase3.h"
#include "MiniChara/MiniCharaTubar.h"
#include "MiniChara/MiniCharaMonkitty.h"
#include "MiniChara/MiniCharaGlocken.h"


MiniChara::MiniChara(const EntityId _miniCharaManager, const Config& _config) :
	GameObject{ "Play/UI/MiniChara.json" },
	manager_{ _miniCharaManager },
	hImage_{ INVALID_HANDLE },
	imageSize_{ Vector2Int::Zero() },
	animTimeLeft_{},
	scale_{ 0.5f },
	pMiniCharaState_{},
	config_{ std::move(_config) }
{
	switch (config_.type)
	{
		case MiniCharaType::Base3:
			pMiniCharaState_ = std::make_unique<MiniCharaBase3>();
			break;
		case MiniCharaType::Tubar:
			pMiniCharaState_ = std::make_unique<MiniCharaTubar>();
			break;
		case MiniCharaType::Monkitty:
			pMiniCharaState_ = std::make_unique<MiniCharaMonkitty>();
			break;
		case MiniCharaType::Glocken:
			pMiniCharaState_ = std::make_unique<MiniCharaGlocken>();
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
	assert(config_.totalAnimTime > 0 && "feild to get total anim time");

	pMiniCharaState_.get()->Init(*this);
}

void MiniChara::Update()
{
	const float DT{ System().Get<GameTime>().GetDeltaTime() };

	if (moveTimeLeft_ > 0.0f)
	{
		moveTimeLeft_ -= DT;
		wassert(config_.moveTime > FLT_EPSILON && "ゼロ除算するな！");
		Vector2 position{ Mathf::Lerp(fromPos_, targetPos_, moveTimeLeft_ / config_.moveTime) };
		drawPosition_ = { static_cast<int>(position.x), static_cast<int>(position.y) };
	}
	
	animTimeLeft_ -= DT;
	if (animTimeLeft_ <= 0.0f)
	{
		animTimeLeft_ += config_.totalAnimTime;
	}

	pMiniCharaState_.get()->Update(*this);
}

void MiniChara::MoveAt(const Vector2Int _position)
{
	moveTimeLeft_ = config_.moveTime;
	fromPos_ = drawPosition_;
	targetPos_ = _position;
}
