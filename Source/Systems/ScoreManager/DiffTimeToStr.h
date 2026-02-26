#pragma once
#include <wtgb.h>


/// <summary>
/// ゲームスコアの到着時間差を文字列に変換する
/// </summary>
class DiffTimeToStr
{
	/// <summary>
	/// 時間差と文字列のペア
	/// </summary>
	using WithinTimeAndString = std::pair<float, std::string>;

public:
	DiffTimeToStr(json& _diffTimeStrings);
	~DiffTimeToStr();

	std::string_view Get(const float _time);

private:
	std::vector<WithinTimeAndString> pairs_;
};

