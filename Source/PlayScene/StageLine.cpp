#include "pch\pch.h"
#include "StageLine.h"

using namespace wtgb;

StageLine::StageLine() : GameObject
{
	[this](GameObjectBuilder& _builder)
	{
		_builder
		.AddComponent<GameObjectProperty>()
			.BeginSetter()
				.name("StageLine")
			.EndSetter()
		.AddComponent<wtgb::Transform>()
			.BeginSetter()
				.scale({ 400.0f, 1, 1 })
			.EndSetter()
		.AddComponent<ModelMesh>()
			.BeginSetter()
				.pOriginalMesh(&this->stageMesh_)
			.EndSetter()
		.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/StageMesh.hlsl")
				.textureConfig(
					{
						.fileName = "GroundTexture.png",
						.filer = D3D11_FILTER_MIN_MAG_MIP_POINT,
						.addressMode = D3D11_TEXTURE_ADDRESS_WRAP,
						.format = DXGI_FORMAT_R8G8B8A8_UNORM,
						.dimension = D3D11_SRV_DIMENSION_TEXTURE2D,
					})
			.EndSetter()
		.AddComponent<Collider>()
			.BeginSetter()
				.colliderType(Collider::Type::Section)
			.EndSetter()
		.Build();
	}
},
	stageMesh_{ points_ }
{
}

StageLine::~StageLine()
{
}

void StageLine::Init()
{
	Collider& collider{ GetComponent<Collider>() };

	// TODO: データはちゃんと移す
	points_ =
	{
		{ 0, 0 },
		{ 80, 40 },
		{ 120, 80 },
		{ 200, 120 },
		{ 240, 180 },
		{ 310, 180 },
		{ 350, 210 },
		{ 430, 310 },
		{ 620, 320 },
	};


	/*for (int i = 0; i < 100; i++)
	{
		Vector2 last{ points_.at(points_.size() - 1) };
		last.x += 10.0f;
		last.y -= 10.0f;
		points_.push_back(last);
	}*/

	// 全ての y 軸を - にする
	for (auto& point : points_)
	{
		point.y = -point.y;
	}

	collider.SetPoints2D(points_);
	stageMesh_.CallInit(System());
}

void StageLine::Update()
{
}

void StageLine::Release()
{
	stageMesh_.CallRelease(System());
}
