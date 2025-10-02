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
const float MICRO_TO_SEC{ 0.0000001f };

wtgb::GameTime::GameTime() :
	isFrameDue_{ false },
	deltaTimeSec_{ 0.0f },
	currentMicro_{},
	previousMicro_{}
{
}

wtgb::GameTime::~GameTime()
{
}

void wtgb::GameTime::Init()
{
	timeBeginPeriod(PERIOD_MILLI);
	BOOL succeed{ QueryPerformanceCounter(&previousMicro_) };
	wassert(succeed && "CPU時間の取得に失敗");
}

void wtgb::GameTime::Update()
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
		deltaTimeSec_ = static_cast<float>(diff) * MICRO_TO_SEC;
		previousMicro_ = currentMicro_;
	}
}

void wtgb::GameTime::End()
{
	timeEndPeriod(PERIOD_MILLI);
}
