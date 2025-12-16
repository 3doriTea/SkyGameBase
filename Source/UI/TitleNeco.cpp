#include "TitleNeco.h"

TitleNeco::TitleNeco() :
	GameObject{ "Simple.json" },
	hImages_{}
{
}

TitleNeco::~TitleNeco()
{
}

void TitleNeco::Init()
{
	ResourceSystem& rc{ System().Get<ResourceSystem>() };

	hImages_[I_HAND] = rc.LoadTexture("TitleNeco-Hand.png");
}

void TitleNeco::Update()
{
}

void TitleNeco::Release()
{
}
