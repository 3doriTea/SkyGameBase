#include "LiftRope.h"
#include "../StageLine.h"
#include "../LiftStructure.h"


LiftRope::LiftRope(const Vector3& _position, const EntityId _stageLine, const EntityId _structure) :
	GameObject
	{
		[this, _position](GameObjectBuilder& _builder)
		{
			_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("LiftRope")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
					.position(_position)
					.scale({ 1.0f, 1, 1 })
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.pOriginalMesh(&this->ropeMesh_)
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
			.Build();
		}
	},
	stageLine_{ _stageLine },
	ropeMesh_{ points_ },
	points_{},
	structure_{ _structure }
{
}

LiftRope::~LiftRope()
{
}

void LiftRope::Init()
{
	StageLine* pStageLine{ FindGameObject<StageLine>(stageLine_) };
	LiftStructure* pStructure{ FindGameObject<LiftStructure>(structure_) };
	wassert(pStageLine && pStructure);

	if (pStageLine && pStructure)
	{
		// 各ポールの間を線で繋いでいく
		for (const LiftStructure::LiftPoleBinding& pole : pStructure->GetPoles())
		{
			float z{ pole.position.z };
			float height{ pStructure->GetRopeHeight(z) };
			
			points_.push_back({ z, height });
		}
		ropeMesh_.CallInit(System());
	}
}

void LiftRope::Update()
{
}

void LiftRope::Release()
{
	ropeMesh_.CallRelease(System());
}
