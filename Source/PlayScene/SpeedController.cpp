#include "SpeedController.h"

SpeedController::SpeedController() :
	GameObject{ "Play/SpeedController.json" },
	speedStopMin_{},
	speedGoodMin_{},
	speedHighMin_{},
	speedGLOCLine_{},
	currentSpeedValue_{},
	previousSpeedValue_{}
{
}

SpeedController::~SpeedController()
{
}

void SpeedController::Init()
{
}

void SpeedController::Update()
{
	// TODO: ターゲットエンティティから速度取得
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
