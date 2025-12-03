#include "pch\pch.h"
#include "DebugPoint.h"

DebugPoint::DebugPoint(const Vector3& _position, const float _scale) : GameObject
{
	[this, &_position, &_scale](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("DebugPoint")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
					.scale(Vector3::One() * _scale)
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.fileName("TestSphere")
				.EndSetter()
		.Build();
	}
},
{
}

DebugPoint::~DebugPoint()
{
}

void DebugPoint::Init()
{
}
