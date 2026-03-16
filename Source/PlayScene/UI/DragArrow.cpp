#include "DragArrow.h"


DragArrow::DragArrow(const EntityId _axis) :
	GameObject{ "Play/DragArrow.json" },
	axis_{ _axis }
{
	GetComponent<GameObjectProperty>().SetParent(axis_);
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
