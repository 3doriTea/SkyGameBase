#include "Alarm.h"
#include "GameTime.h"

wtgb::Alarm::Alarm()
{
}

wtgb::Alarm::~Alarm()
{
}

wtgb::Result wtgb::Alarm::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Alarm::Update(const ViewerUpdate& _system)
{
	const float DT{ _system.Get<GameTime>().GetDeltaTime() };

	for (auto& [hAlarm, content] : registry_)
	{
		// カウントダウンタイマーを進める
		content.timeLeft -= DT;

		if (content.timeLeft <= 0.0f)
		{

		}
	}
}

void wtgb::Alarm::End()
{
}

void wtgb::Alarm::Add(const std::function<void()>& _callback, const float _time)
{
}
