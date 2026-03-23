#include "DragArrow.h"


DragArrow::DragArrow(const EntityId _axis) :
	GameObject{ "Play/DragArrow.json" },
	axis_{ _axis }
{
	GetComponent<GameObjectProperty>().SetParent(axis_);
	Transform().SetRotation(Vector3::Up() * DirectX::XM_PI);
	Transform().SetPosition(Vector3::Forward() * 0.5f);
}

DragArrow::~DragArrow()
{
}

void DragArrow::Init()
{
}

void DragArrow::Update()
{
}

void DragArrow::Release()
{
}
