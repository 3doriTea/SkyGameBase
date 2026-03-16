#include "DragArrowAxis.h"

DragArrowAxis::DragArrowAxis(const EntityId _player) :
	GameObject{ "Simple.json" },
	player_{ _player }
{
}

DragArrowAxis::~DragArrowAxis()
{
}

void DragArrowAxis::Init()
{
}

void DragArrowAxis::Update()
{
	Vector3 position{ FindGameObject(player_)->Transform().GetPosition() };
	Transform().SetPositionWorld(position);
}

void DragArrowAxis::Release()
{
}

void DragArrowAxis::SetScaleZ(const float _z)
{
	Transform().SetScale(Vector3{ 5.0f, 5.0f, 5.0f * (_z + 1.0f) });
}

void DragArrowAxis::SetAngleY(const float _angle)
{
	Transform().SetRotation(Vector3::Up() * _angle);
}
