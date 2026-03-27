#include "pch/pch.h"
#include "TitleCamera.h"
#include "TitleNeco.h"


TitleCamera::TitleCamera(const EntityId _titleNeco) :
	GameObject{ "Title/TitleCamera.json" },
	titleNeco_{ _titleNeco },
	position_{},
	targetBegin_{},
	targetEnd_{}
{
}

TitleCamera::~TitleCamera()
{
}

void TitleCamera::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	Camera& camera{ System().Get<Camera>() };
	camera.position_ = position_;
	camera.targetPosition_ = targetBegin_;
}

void TitleCamera::Update()
{
	Camera& camera{ System().Get<Camera>() };

	TitleNeco* dragCircle{ dynamic_cast<TitleNeco*>(FindGameObject(titleNeco_)) };
	
	if (dragCircle)
	{
		float raito{ dragCircle->GetMoveRaito() };
		camera.targetPosition_ = Mathf::Lerp(
			targetBegin_,
			targetEnd_,
			raito);
	}
}

void TitleCamera::Release()
{
}

void TitleCamera::OnLoadParam(const json& _json)
{
	position_    = SafeGet<Vector3>(_json, "position");
	targetBegin_ = SafeGet<Vector3>(_json, "targetBegin");
	targetEnd_   = SafeGet<Vector3>(_json, "targetEnd");
}
