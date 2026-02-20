#include "SpeedController.h"


SpeedController::SpeedController(const EntityId _targetEntity) :
	GameObject{ "Play/SpeedController.json" },
	speedStopMin_{},
	speedGoodMin_{},
	speedHighMin_{},
	speedGLOCLine_{},
	currentSpeedValue_{},
	previousSpeedValue_{},
	targetEntity_{ _targetEntity }
{
}

SpeedController::~SpeedController()
{
}

void SpeedController::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
}

void SpeedController::Update()
{
	using DirectX::XMVector3Length;
	using DirectX::XMVectorGetX;

	// ひたすらターゲットの速度を取得して更新する

	const float FPS{ System().Get<GameTime>().GetFPS() };

	GameObject* pTargetGameObject{ FindGameObject(targetEntity_) };
	wassert(pTargetGameObject && "スピードコントロール対象が見つからなかった");

	RigidBody& targetRB{ pTargetGameObject->GetComponent<RigidBody>() };
	float speedPerSec{ XMVectorGetX(XMVector3Length(targetRB.GetVelocity())) };

	// RigidBody - Velocityは1秒間あたりの速度であるため、1フレーム当たりの速度に変換
	wassert(FPS != 0 && "FPSが0による0除算が発生するよ");
	SetSpeed(speedPerSec / FPS);

	LOGFLN("Speed:{}", speedPerSec / FPS);
}

void SpeedController::Release()
{
}

float SpeedController::GetGreyOutRatio() const
{
	return Mathf::InvLerp(speedHighMin_, speedGLOCLine_, currentSpeedValue_);
}

bool SpeedController::IsGLOC() const
{
	return currentSpeedValue_ >= speedGLOCLine_;
}

SpeedType SpeedController::GetSpeedType() const
{
	if (currentSpeedValue_ <= speedStopMin_)
	{
		return SpeedType::Stop;  // 止まっている判定
	}
	else if (currentSpeedValue_ < speedGoodMin_)
	{
		return SpeedType::TooSlow;  // 良くない遅い速度
	}
	else if (currentSpeedValue_ < speedHighMin_)
	{
		return SpeedType::Good;  // 速すぎない良い速度
	}
	else  // 速すぎる
	{
		return SpeedType::Excissive;
	}
}

void SpeedController::SetSpeed(const float _perFrame)
{
	previousSpeedValue_ = currentSpeedValue_;
	currentSpeedValue_ = _perFrame;
}

void SpeedController::OnLoadParam(const json& _json)
{
	speedStopMin_ = SafeGet<float>(_json, "speedStopMin");
	speedGoodMin_ = SafeGet<float>(_json, "speedGoodMin");
	speedHighMin_ = SafeGet<float>(_json, "speedHighMin");
	speedGLOCLine_ = SafeGet<float>(_json, "speedGLOCLine");
}
