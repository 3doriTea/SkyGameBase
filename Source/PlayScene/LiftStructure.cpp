#include "LiftStructure.h"
#include "StageLine.h"
#include "Lift/LiftChair.h"
#include "Lift/LiftLoop.h"


LiftStructure::LiftStructure(const EntityId _stage, const float _polePosX) :
	GameObject
	{
		"LiftStructure.json"
	},
	stage_{ _stage },
	polePosX_{ _polePosX }
{
}

LiftStructure::~LiftStructure()
{
}

void LiftStructure::Init()
{
	OnLoad(GetComponent<Parameter>().Load());

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
		position.x = ropeSpasing_ * 0.5f + polePosX_;
		// 逆方向から引いていく
		position.z = totalLength_ - (_length - curveLength_ - laneLength_);
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

	// 椅子の座標と回転(ラジアン)を返す
	return { position, angleRadian };
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

void LiftStructure::OnLoad(const json& _json)
{
	ropeSpasing_ = SafeGet<float>(_json, "ropeSpasing");
	chairsCount_ = SafeGet<int>(_json, "chairsCount");
	poleDistance_ = SafeGet<float>(_json, "poleDistance");
	ropeHeight_ = SafeGet<float>(_json, "ropeHeight");
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
		instantiatedEntity = pPlayScene->Instantiate<LiftLoop>(
			GetPolePosition(currZ), parentEntity);

		while (currZ < STAGE_LENGTH_Z)
		{
			// ポールを立てていく
			instantiatedEntity = pPlayScene->Instantiate<LiftPole>(GetPolePosition(currZ), parentEntity);
			poles_.push_back(instantiatedEntity);
			currZ += POLE_DISTANCE;
		}

		currZ -= POLE_DISTANCE;

		// 最後のループ端を設置 (ポールと重複する)
		loopPole_[LOOP_POLE_LOWER] = pPlayScene->Instantiate<LiftLoop>(GetPolePosition(currZ), parentEntity);
	}
}

void LiftStructure::GenerateChairs()
{
	GameScene* pPlayScene{ GetScene() };
	if (pPlayScene)
	{
		pPlayScene->Instantiate<LiftChair>(GetEntityId(), 0.0f, totalLength_);

	}
}
