#include "pch\pch.h"
#include "GameTime.h"
#include <mmsystem.h>

const UINT wtgb::GameTime::PERIOD_MILLI{ 1 };  // ï™âî\Çê›íË
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
	QueryPerformanceCounter(&previousMicro_);
}

void wtgb::GameTime::Update()
{

}

void wtgb::GameTime::End()
{
	timeEndPeriod(PERIOD_MILLI);
}
