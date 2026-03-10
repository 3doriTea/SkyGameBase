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

	std::vector<AlarmHandle> toRemoveHandles;
	for (auto& [hAlarm, content] : registry_)
	{
		// カウントダウンタイマーを進める
		content.timeLeft -= DT;

		if (content.timeLeft <= 0.0f)
		{
			// 時間が来たら呼び出して削除予定に追加
			content.callback();
			toRemoveHandles.push_back(hAlarm);
		}
	}

	// 削除予定のハンドルを全部削除していく
	for (AlarmHandle handle : toRemoveHandles)
	{
		registry_.Remove(handle);
	}
}

void wtgb::Alarm::End()
{
}

wtgb::AlarmHandle wtgb::Alarm::Add(const std::function<void()>& _callback, const float _time)
{
	return registry_.Emplace(_callback, _time);
}

void wtgb::Alarm::Cancel(const AlarmHandle _hAlarm)
{
	registry_.Remove(_hAlarm);
}

wtgb::Alarm::AlarmPair::AlarmPair(
	const std::function<void()>& _callback,
	const float _timeLeft) :
	callback{ _callback },
	timeLeft{ _timeLeft }
{
}
