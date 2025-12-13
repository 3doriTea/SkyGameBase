#include "pch\pch.h"
#include "StageLine.h"

using namespace wtgb;

namespace
{
	const float GOAL_HEIGHT{ 3000.0f };
	const float GOAL_POS_Y{ -GOAL_HEIGHT };
	const float RAND_RANGE_X{ 100.0f };
	const float RAND_RANGE_Y{ 30.0f };

	const float GOAL_SIZE_Z{ 300.0f };
	const float GOAL_WALL_HEIGHT{ 300.0f };
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
	ifs.close();

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
	last = points_.at(points_.size() - 1);


	// 床を作る
	last.x += GOAL_SIZE_Z;
	points_.push_back(last);

	// 壁を作る
	last.y -= GOAL_WALL_HEIGHT;
	points_.push_back(last);

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
	using namespace DirectX;

	for (int i = 0; i < points_.size() - 1; i++)
	{
		Vector2 begin{ points_[i] };
		Vector2 end{ points_[i + 1] };
		Vector2 v{ end - begin };
		Vector2 w{ Vector2{ _worldPosition.z, _worldPosition.y } - begin};
		const float SEGMENT_LENGTH_SQ{ XMVectorGetX(XMVector2LengthSq(v)) };

		if (begin.x <= _worldPosition.z && _worldPosition.z < end.x)
		{  // 範囲内なら
			// 最近接点
			Vector2 point2D{};

			// 線分に垂直な法線ベクトル（仮）
			Vector2 SEGMENT_NORM{ XMVector2Normalize(Vector2{ -v.y, v.x }) };

			// 法線が上を向くように調整 (地形として扱うため、常に円が存在すべき側を指すようにする)
			// 一般に+Yが上であれば、法線のY成分が負なら反転させる
			if (SEGMENT_NORM.y < 0.0f)
			{
				SEGMENT_NORM = SEGMENT_NORM * -1.0f;
			}

			// 線分がもうほぼ点と言って過言ではない (端点衝突)
			if (SEGMENT_LENGTH_SQ < FLT_EPSILON)
			{
				point2D = begin;
			}
			else // 線分としての処理
			{
				// 線分上での接点の割合 t
				float t{ XMVectorGetX(XMVector2Dot(w, v)) / SEGMENT_LENGTH_SQ };

				if (t < 0.0f) // 始点より前にある -> 始点が最近接点
				{
					point2D = begin;
				}
				else if (t > 1.0f) // 終点より後にある -> 終点が最近接点
				{
					point2D = end;
				}
				else // 線分の間 -> 垂直な点が最近接点
				{
					point2D = v * t + begin;
				}
			}

			return point2D.y;
		}
	}
	return _worldPosition.y;
}
