#include "pch\pch.h"
#include "GameTime.h"
#include <mmsystem.h>
#include "WTGBAssert.h"
#include "LogUtility.h"

namespace
{
	const int FPS{ 60 };
}

const UINT wtgb::GameTime::PERIOD_MILLI{ 1 };  // 分解能を設定
const LONGLONG wtgb::GameTime::ONE_SEC_TO_MICRO{ 1000000 };
const float wtgb::GameTime::MICRO_TO_SEC{ 0.0000001f };

wtgb::GameTime::GameTime() :
	isFrameDue_{ false },
	deltaTimeSec_{ 0.0f },
	currentMicro_{},
	previousMicro_{},
	timeScale_{ 1.0f },
	timeScalePrev_{ 1.0f }
{
}

wtgb::GameTime::~GameTime()
{
}

void wtgb::GameTime::SetTimeStopped(const bool _timeStopped)
{
	if (_timeStopped)
	{
		timeScale_ = 0.0f;  // 時間を完全停止
		deltaTimeSec_ = 0.0f;
	}
	else
	{
		timeScale_ = timeScalePrev_;
	}
}

void wtgb::GameTime::SetTimeScale(const float _timeScale)
{
	timeScale_ = _timeScale;
	timeScalePrev_ = timeScale_;
}

const float wtgb::GameTime::GetFPS() const
{
	return FPS;
}

wtgb::Result wtgb::GameTime::Init(const ViewerInit& _viewer)
{
	timeBeginPeriod(PERIOD_MILLI);
	BOOL succeed{ QueryPerformanceCounter(&previousMicro_) };
	wassert(succeed && "CPU時間の取得に失敗");

	if (succeed)
	{
		return Result::Code::Succeed;
	}
	else
	{
		return Result::Code::Failed;
	}
}

void wtgb::GameTime::Update(const ViewerUpdate& _system)
{
	if (QueryPerformanceCounter(&currentMicro_) == FALSE)
	{
		LOGFW("CPU時間取得に失敗");
		return;
	}

	// 前フレームと今のマイクロ秒差
	const LONGLONG diff{ currentMicro_.QuadPart - previousMicro_.QuadPart };
	// 差をFPS倍して1秒を超える = 差が 1 / FPS なら更新タイミング
	isFrameDue_ = (diff * FPS >= ONE_SEC_TO_MICRO);
	
	// 更新タイミングなら
	if (isFrameDue_)
	{
		deltaTimeSec_ = static_cast<float>(diff) * MICRO_TO_SEC * timeScale_;
		previousMicro_ = currentMicro_;
	}
}

void wtgb::GameTime::End()
{
	timeEndPeriod(PERIOD_MILLI);
}
