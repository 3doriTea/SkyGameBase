#include "pch/pch.h"
#include "TitleCamera.h"
#include "TitleNeco.h"

namespace
{
	static const Vector3 CAMERA_POSITION{ 295, -151, 411 };
	static const Vector3 CAMERA_TARGET_UP{ 144, -144, 41 };
	static const Vector3 CAMERA_TARGET_DOWN{ 144, -288, 41 };
}

TitleCamera::TitleCamera(const EntityId _titleNeco) :
	GameObject{ "Simple.json" },
	titleNeco_{ _titleNeco }
{
}

TitleCamera::~TitleCamera()
{
}

void TitleCamera::Init()
{
	Camera& camera{ System().Get<Camera>() };
	camera.position_ = CAMERA_POSITION;
	camera.targetPosition_ = CAMERA_TARGET_UP;
}

void TitleCamera::Update()
{
	Camera& camera{ System().Get<Camera>() };

	TitleNeco* dragCircle{ dynamic_cast<TitleNeco*>(FindGameObject(titleNeco_)) };
	
	if (dragCircle)
	{
		float raito{ dragCircle->GetMoveRaito() };
		camera.targetPosition_ = Mathf::Lerp(CAMERA_TARGET_UP, CAMERA_TARGET_DOWN, raito);
	}
}

void TitleCamera::Release()
{
}
