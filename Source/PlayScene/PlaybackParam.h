#pragma once


/// <summary>
/// smfを再生するときの設定
/// </summary>
struct PlaybackParam
{
	float normalPlayRatio;   // 通常の再生倍率
	float stoppedPlayRatio;  // 停止中の再生倍率
};

// jsonに自動変換する関数群
namespace
{
	inline void to_json(json& j, const PlaybackParam& _param)
	{
		j = json
		{
			{ "normalPlayRatio", _param.normalPlayRatio },
			{ "stoppedPlayRatio", _param.stoppedPlayRatio }
		};
	}

	inline void from_json(const json& j, PlaybackParam& _param)
	{
		j.at("normalPlayRatio").get_to(_param.normalPlayRatio);
		j.at("stoppedPlayRatio").get_to(_param.stoppedPlayRatio);
	}
}
