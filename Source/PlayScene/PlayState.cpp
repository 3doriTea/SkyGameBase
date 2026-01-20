#include "PlayState.h"

PlayState::PlayState() :
	GameObject{ "PlayState.json" },
	pCurrentState_{}
{
}

PlayState::~PlayState()
{
}

void PlayState::Init()
{
}

void PlayState::Update()
{
	if (pCurrentState_)
	{
		pCurrentState_->Update(System());
	}
}

void PlayState::Release()
{
}

void PlayState::ChangeState(Type _type)
{
	switch (_type)
	{
	case PlayState::Type::StartLine:
		pCurrentState_ = std::make_unique<StartLine>();
		break;
	case PlayState::Type::Falling:
		pCurrentState_ = std::make_unique<Falling>();
		break;
	case PlayState::Type::Finished:
		pCurrentState_ = std::make_unique<Finished>();
		break;
	default:
		wassert(false && "未対応のプレイステート");
		break;
	}
}

PlayState::Type PlayState::GetState() const
{
	wassert(pCurrentState_ && "現在のステートがnullptr");
	
	return pCurrentState_->GetType();
}

void PlayState::StartLine::Update(ViewerCached _system)
{
}

void PlayState::Falling::Update(ViewerCached _system)
{
}

void PlayState::Finished::Update(ViewerCached _system)
{
}
