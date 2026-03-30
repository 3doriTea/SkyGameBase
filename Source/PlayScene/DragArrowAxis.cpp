#include "DragArrowAxis.h"

DragArrowAxis::DragArrowAxis(const EntityId _player) :
	GameObject{ "Play/DragArrowAxis.json" },
	player_{ _player },
	scaleZDiv_{ 1.0f },
	scaleBase_{ 0.0f },
	offset_{ Vector3::Zero() }
{
}

DragArrowAxis::~DragArrowAxis()
{
}

void DragArrowAxis::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void DragArrowAxis::Update()
{
	Vector3 position{ FindGameObject(player_)->Transform().GetPosition() };
	Transform().SetPositionWorld(position + offset_);
}

void DragArrowAxis::Release()
{
}

void DragArrowAxis::SetScaleZ(const float _z)
{
	float offset{ 1.0f };
	Transform().SetScale(Vector3
		{
			scaleBase_,
			scaleBase_,
			scaleBase_ * (_z / scaleZDiv_ + offset)
		});

}

void DragArrowAxis::SetAngleY(const float _angle)
{
	Transform().SetRotation(Vector3::Up() * _angle);
}

void DragArrowAxis::OnLoadParam(const json& _j)
{
	scaleBase_ = SafeGet<float>(_j, "scaleBase");
	scaleZDiv_ = SafeGet<float>(_j, "scaleZDiv");
	offset_ = SafeGet<Vector3>(_j, "offset");
}
