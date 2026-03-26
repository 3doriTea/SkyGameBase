#include "SkySphere.h"


SkySphere::SkySphere(
	const EntityId _cameraEntity,
	const float _angleYRadian) :
	GameObject{ "SkySphere.json" },
	angleYRadian_{ _angleYRadian }
{
	Property().SetParent(_cameraEntity);  // 常にカメラにくっつくようにする
	Transform().SetRotation(Vector3::Up() * _angleYRadian);
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
