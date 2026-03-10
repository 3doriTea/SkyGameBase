#include "SkySphere.h"

SkySphere::SkySphere() :
	GameObject{ "SkySphere.json" }
{
	EntityId mainCamera{ FindGameObject("CameraController")->GetEntityId() };
	Property().SetParent(mainCamera);  // 常にカメラにくっつくようにする
}

SkySphere::~SkySphere()
{
}

void SkySphere::Init()
{
}

void SkySphere::Update()
{
}

void SkySphere::Release()
{
}
