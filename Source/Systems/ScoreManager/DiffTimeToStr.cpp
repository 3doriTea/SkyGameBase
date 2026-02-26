#include "DiffTimeToStr.h"

DiffTimeToStr::DiffTimeToStr(json& _diffTimeStrings)
{
	wassert(_diffTimeStrings.is_array());

	for (const auto& diffTimeString : _diffTimeStrings.array())
	{
		float diffTime{ diffTimeString.at("within").get<float>() };
		std::string str{ diffTimeString.at("string").get<std::string>() };

		pairs_.emplace_back(diffTime, str);
	}
}

DiffTimeToStr::~DiffTimeToStr()
{
}

std::string_view DiffTimeToStr::Get(const float _time)
{
	// _timeより大きい最初の要素を見つける
	auto itr
	{
		std::upper_bound(
			pairs_.begin(),
			pairs_.end(),
			_time,
			[](const float _time, const WithinTimeAndString& _pair)
			{
				return _time < _pair.first;
			})
	};

	// 見つからなかったのなら、最後の文字列を返す
	if (itr == pairs_.end())
	{
		return pairs_.back().second;
	}

	return itr->second;
}
