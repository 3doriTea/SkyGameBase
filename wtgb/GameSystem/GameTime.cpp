#include "pch\pch.h"
#include "GameTime.h"
#include <mmsystem.h>
#include "WTGBAssert.h"
#include "LogUtility.h"

const UINT wtgb::GameTime::PERIOD_MILLI{ 1 };  // •ª‰ğ”\‚ğİ’è
const LONGLONG wtgb::GameTime::ONE_SEC_TO_MICRO{ 1000000 };

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
	wassert(succeed && "CPUŠÔ‚Ìæ“¾‚É¸”s");
}

void wtgb::GameTime::Update()
{
	if (QueryPerformanceCounter(&currentMicro_) == FALSE)
	{
		LOGFW("CPUŠÔæ“¾‚É¸”s");
		return;
	}
}

void wtgb::GameTime::End()
{
	timeEndPeriod(PERIOD_MILLI);
}
