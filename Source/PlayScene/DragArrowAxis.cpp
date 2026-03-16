#include "DragArrowAxis.h"

DragArrowAxis::DragArrowAxis(const EntityId _player) :
	GameObject{ "Simple.json" }
{
	Property().SetParent(_player);
}

DragArrowAxis::~DragArrowAxis()
{
}

void DragArrowAxis::Init()
{
}

void DragArrowAxis::Update()
{
}

void DragArrowAxis::Release()
{
}

void DragArrowAxis::SetScaleZ(const float _z)
{
	Transform().SetScale(Vector3{ 1.0f, 1.0f, _z });
}

void DragArrowAxis::SetAngleY(const float _angle)
{
	Transform().SetRotation(Vector3::Up() * _angle);
}
