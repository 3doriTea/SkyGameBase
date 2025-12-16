#include "pch/pch.h"
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

	fs::path dir{ "./Image/Title" };

	hImages_[I_HAND] = rc.LoadTexture(dir / "TitleNeco-Hand.png");
	hImages_[I_HANG] = rc.LoadTexture(dir / "TitleNeco-Hang.png");
	hImages_[I_NORM] = rc.LoadTexture(dir / "TitleNeco-Norm.png");
}

void TitleNeco::Update()
{
}

void TitleNeco::Release()
{
}
