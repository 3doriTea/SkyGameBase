#include "pch/pch.h"
#include "TitleMountain.h"
#include "Stage/StageLoader.h"


TitleMountain::TitleMountain() : GameObject
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
	stageMesh_{ points_, textureScale_ }
{
}

void TitleMountain::Init()
{
	Collider& collider{ GetComponent<Collider>() };

	StageLoader stageLoader{ points_, nullptr, textureScale_ };
	bool succeed{ stageLoader.TryLoad("TitleMountain.json") };
	wassert(succeed && "タイトル山のデータ読み込みに失敗");

	// 全ての y 軸を - にする
	for (auto& point : points_)
	{
		point.y = -point.y;
	}

	collider.SetPoints2D(points_);
	stageMesh_.CallInit(System());
}
