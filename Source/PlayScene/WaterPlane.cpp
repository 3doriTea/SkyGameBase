#include "pch\pch.h"
#include "WaterPlane.h"

using namespace wtgb;

WaterPlane::WaterPlane(const Vector3& _localPos, const Vector2Int _size) : GameObject
{
	[this, &_localPos](GameObjectBuilder& _builder)
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("WaterPlane")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.position(_localPos)
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				.pOriginalMesh(&this->waterMesh_)
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/Simple3D.hlsl")
			.EndSetter()
		/*.AddComponent<Collider>()
			.BeginSetter()
				.colliderType()
			.EndSetter()*/
		.Build();
	}
},
	waterMesh_{ pointsHeight_, _size }
{
}

WaterPlane::~WaterPlane()
{
}

void WaterPlane::Init()
{
	waterMesh_.CallInit(System());
}

void WaterPlane::Update()
{
}

void WaterPlane::Release()
{
	waterMesh_.CallRelease(System());
}
