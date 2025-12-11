#include "pch\pch.h"
#include "StageLine.h"

using namespace wtgb;

namespace
{
	const float GOAL_HEIGHT{ 5000.0f };
	const float GOAL_POS_Y{ -GOAL_HEIGHT };
	const float RAND_RANGE_X{ 100.0f };
	const float RAND_RANGE_Y{ 30.0f };
}

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

	std::ifstream ifs{ "StageData.json" };
	json j{};

	ifs >> j;

	const size_t POINTS_SIZE{ j["points"].size() };

	points_.resize(POINTS_SIZE);

	// jsonから一部ステージを読み取ってくる
	for (size_t i = 0; i < POINTS_SIZE; i++)
	{
		Vector2 pos
		{
			j["points"][i]["x"].get<float>(),
			j["points"][i]["y"].get<float>()
		};
		points_.push_back(pos);
	}

	Mathf::Randomer random{ 0 };

	Vector2 last{};
	while (last.y < GOAL_HEIGHT)
	{
		last = points_.at(points_.size() - 1);
		points_.push_back({ last.x + (random.Rand() * RAND_RANGE_X), last.y + random.Rand() * RAND_RANGE_Y });
	}

	points_.at(points_.size() - 1).y = GOAL_HEIGHT;

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

float StageLine::GetPosY(const Vector3& _worldPosition)
{
	return _worldPosition.y;
}
