#include "pch\pch.h"
#include "StageLine.h"
#include "Stage/StageLoader.h"

using namespace wtgb;

StageLine::StageLine(const StageLineConfig& _config) :
	GameObject
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
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.pOriginalMeshes(&this->stageMesh_)
				.EndSetter()
			.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/StageMeshes.hlsl")
					.textureConfig(
						{
							.fileName = "GroundTexture2.png",
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
	config_{ _config },
	textureScale_{ 0.0f },
	stageMesh_{ points_, textureScale_ }
{
	Transform().SetScale(config_.stageScale);
}

StageLine::~StageLine()
{
}

void StageLine::Init()
{
	Collider& collider{ GetComponent<Collider>() };

	StageLoader stageLoader{ points_, textureScale_ };
	bool succeed{ stageLoader.TryLoad("StageData.json") };
	wassert(succeed && "タイトル山のデータ読み込みに失敗");

	Mathf::Randomer random{ 0 };

	Vector2 last{};
	while (last.y < config_.goalHeight)
	{
		last = points_.at(points_.size() - 1);
		points_.push_back({ last.x + (random.Rand() * config_.randRangeX), last.y + random.Rand() * config_.randRangeY });
	}

	points_.at(points_.size() - 1).y = config_.goalHeight;
	last = points_.at(points_.size() - 1);


	// 床を作る
	last.x += config_.goalSizeZ;
	points_.push_back(last);

	// 壁を作る
	last.y -= config_.goalWallHeight;
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

	// それより奥は最後の高さを維持
	return points_.back().y;
}

float StageLine::GetStageLengthZ() const
{
	if (points_.empty())
	{
		return 0.0f;  // ステージポイントがないなら 0.0f
	}

	// ステージポイント末端のx軸がステージの長さになる
	return points_.back().x;
}
