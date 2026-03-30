#include "LiftStructure.h"
#include "StageLine.h"
#include "Lift/LiftChair.h"
#include "Lift/LiftLoop.h"
#include "Lift/LiftPole.h"
#include "Lift/LiftRope.h"
#include "LiftChilds/Cloud.h"


LiftStructure::LiftStructure(const EntityId _stage, const float _polePosX) :
	GameObject
	{
		"LiftStructure.json"
	},
	ropeSpasing_{},
	chairsCount_{},
	poleDistance_{},
	ropeHeight_{},
	ropeWidth_{},
	stage_{ _stage },
	polePosX_{ _polePosX },
	poles_{},
	chairs_{},
	totalLength_{},
	laneLength_{},
	curveLength_{}
{
}

LiftStructure::~LiftStructure()
{
}

void LiftStructure::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());

	StageLine* pStage{ FindGameObject<StageLine>(stage_) };
	wassert(pStage && "ステージラインオブジェクトが見つからない");
	if (pStage == nullptr)
	{
		return;
	}
	// 直線部分の1本の長さ
	laneLength_ = pStage->GetStageLengthZ();

	// カーブ部分の長さ
	curveLength_ = DirectX::XM_PIDIV2 * ropeSpasing_;

	totalLength_ = (laneLength_ * 2.0f)  // 2つの直線ロープ
		+ (curveLength_ * 2.0f);  // 両端の円周

	GeneratePoles();
	GenerateChairs();

	GameScene* pGameScene{ GetScene() };
	wassert(pGameScene && "シーンが見つからなかった");
	if (pGameScene)
	{
		float posY{ poles_.begin()->position.y + ropeHeight_ };

		EntityId liftRopeLeft
		{
			pGameScene->Instantiate<LiftRope>(
				Vector3{ polePosX_ + ropeSpasing_ * -0.5f - ropeWidth_ * 0.5f, posY, 0.0f },
				ropeWidth_,
				stage_,
				GetEntityId())
		};
		EntityId rightRopeLeft
		{
			pGameScene->Instantiate<LiftRope>(
				Vector3{ polePosX_ + ropeSpasing_ * 0.5f - ropeWidth_ * 0.5f, posY, 0.0f },
				ropeWidth_,
				stage_,
				GetEntityId())
		};
	}
}

void LiftStructure::Update()
{
}

void LiftStructure::Release()
{
}

std::tuple<Vector3, float> LiftStructure::GetChairPositionAndRotateY(const float _length)
{
	float lengthAt{ 0.0f };
	Vector3 position{ Vector3::Zero() };
	float angleRadian{ 0.0f };

	if (_length)

	// 下りレーン
	if (lengthAt += laneLength_; _length < lengthAt)
	{
		angleRadian += 0.0f;
		position.x = ropeSpasing_ * 0.5f + polePosX_;
		position.z = _length;
		position.y = GetRopeHeight(position.z);
	}
	// 麓のカーブ
	else if (lengthAt += curveLength_; _length < lengthAt)
	{
		position = poles_.back().GetChairPositionAndRotateY(ropeHeight_);
		float rotateRate{ (_length - laneLength_) / curveLength_ };
		float radius{ ropeSpasing_ * 0.5f };
		position.x += std::cosf(DirectX::XM_PI * rotateRate) * radius;
		position.z += std::sinf(DirectX::XM_PI * rotateRate) * radius;
		angleRadian += radius;
	}
	// 上りレーン
	else if (lengthAt += laneLength_; _length < lengthAt)
	{
		angleRadian += DirectX::XM_PI;
		position.x = -ropeSpasing_ * 0.5f + polePosX_;
		// 逆方向から引いていく
		position.z = laneLength_ - (_length - curveLength_ - laneLength_);
		position.y = GetRopeHeight(position.z);
	}
	// 頂上のカーブ
	else
	{
		lengthAt += curveLength_;
		float length{ _length };
		if (length > lengthAt)
		{
			length = lengthAt;  // 最大値を超えているならクランプする
		}

		position = poles_.front().GetChairPositionAndRotateY(ropeHeight_);
		float rotateRate{ (length - laneLength_) / curveLength_ };
		float radius{ ropeSpasing_ * 0.5f };
		// 各回転を180度反転する
		position.x += std::cosf(DirectX::XM_PI * rotateRate + DirectX::XM_PI) * radius;
		position.z += std::sinf(DirectX::XM_PI * rotateRate + DirectX::XM_PI) * radius;
		angleRadian += radius + DirectX::XM_PI;
	}

	Vector3 offset{ Transform().GetPosition() };

	// 椅子の座標と回転(ラジアン)を返す
	return { position + offset, angleRadian };
}

float LiftStructure::GetRopeHeight(const float _z)
{
	if (_z <= 0.0f)
	{
		// 頂上のポール以下なら頂上のポールの高さ
		return poles_.front().GetChairPositionAndRotateY(ropeHeight_).y;
	}
	else if (_z >= laneLength_)
	{
		// 麓のポール以上なら麓のポールの高さ
		return poles_.back().GetChairPositionAndRotateY(ropeHeight_).y;
	}
	else
	{
		// 間の高さはポール間の線形補間
		size_t beginIndex{ static_cast<unsigned int>(_z / poleDistance_) };
		size_t endIndex{ beginIndex + 1 };
		Vector3 beginPos{ poles_[beginIndex].GetChairPositionAndRotateY(ropeHeight_) };
		Vector3 endPos{ poles_[endIndex].GetChairPositionAndRotateY(ropeHeight_) };
		float rate
		{
			std::fmodf(_z, poleDistance_) / poleDistance_
		};

		return Mathf::Lerp(beginPos, endPos, rate).y;
	}
}

Vector3 LiftStructure::GetPolePosition(const float _z)
{
	StageLine* pStage{ FindGameObject<StageLine>(stage_) };
	wassert(pStage && "ステージラインオブジェクトが見つからない");

	return { polePosX_, pStage->GetPosY(Vector3::Forward() * _z), _z};
}

void LiftStructure::OnLoadParam(const json& _json)
{
	ropeSpasing_ = SafeGet<float>(_json, "ropeSpasing");
	chairsCount_ = SafeGet<int>(_json, "chairsCount");
	poleDistance_ = SafeGet<float>(_json, "poleDistance");
	ropeHeight_ = SafeGet<float>(_json, "ropeHeight");
	ropeWidth_ = SafeGet<float>(_json, "ropeWidth");
}

EntityId LiftStructure::FindChair(const Vector3 _position, const LiftChairDir _dir)
{
	float minDistD{ FLT_MAX };             // 今まで見つけた最小距離の2乗
	EntityId minEntity{ INVALID_ENTITY };  // 今まで見つけた最も近い椅子

	for (const EntityId chair : chairs_)
	{
		GameObject* pPick{ FindGameObject(chair) };
		if (!pPick)
		{
			wassert(false && "無効な座椅子エンティティが格納されていた");
			continue;  // エンティティが見つからなかったなら無視
		}
		Vector3 pickPos{ pPick->Transform().GetPosition() };
		float pickDistD{ DirectX::XMVectorGetX(DirectX::XMVector3LengthSq(pickPos - _position)) };

		float dot
		{ 
			DirectX::XMVectorGetX(
				DirectX::XMVector3Dot(pPick->Transform().GetForward(), Vector3::Forward()))
		};

		if (minDistD > pickDistD && dot > 0)
		{
			minDistD = pickDistD;
			minEntity = chair;
		}
	}

	return minEntity;
}

void LiftStructure::GeneratePoles()
{
	StageLine* pStage{ FindGameObject<StageLine>(stage_) };
	wassert(pStage && "ステージラインオブジェクトが見つからない");

	GameScene* pPlayScene{ GetScene() };

	if (pStage && pPlayScene)
	{
		const float STAGE_LENGTH_Z{ pStage->GetStageLengthZ() };
		float currZ{ 0.0f };

		EntityId instantiatedEntity{ INVALID_ENTITY };

		// 最初のループはじめを設置 (ポールと重複する)
		Vector3 position{ GetPolePosition(currZ) };
		instantiatedEntity = pPlayScene->Instantiate<LiftLoop>(
			position, GetEntityId());

		poles_.push_back({ position, instantiatedEntity });

		while (currZ < STAGE_LENGTH_Z)
		{
			currZ += poleDistance_;
			// ポールを立てていく
			position = GetPolePosition(currZ);
			instantiatedEntity = pPlayScene->Instantiate<LiftPole>(position, GetEntityId());
			poles_.push_back({ position, instantiatedEntity });
		}

		position = GetPolePosition(currZ);
		// 最後のループ端を設置 (ポールと重複する)
		instantiatedEntity = pPlayScene->Instantiate<LiftLoop>(
			position,
			GetEntityId());

		Vector3 offset{ Transform().GetPosition() };
		poles_.push_back({ position + offset, instantiatedEntity });
	}
}

void LiftStructure::GenerateChairs()
{
	GameScene* pPlayScene{ GetScene() };
	if (pPlayScene)
	{
		chairs_.clear();
		wassert(poleDistance_ != 0.0f && "ゼロ除算すんな！");
		for (float length{ 0.0f }; length < totalLength_; length += poleDistance_)
		{
			EntityId liftChair
			{
				pPlayScene->Instantiate<LiftChair>(
					GetEntityId(),
					length,
					totalLength_)
			};

			chairs_.push_back(liftChair);
		}

	}
}
