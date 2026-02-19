#pragma once


/// <summary>
/// smf‚ğÄ¶‚·‚é‚Æ‚«‚Ìİ’è
/// </summary>
struct PlaybackParam
{
	float normalPlayRatio;   // ’Êí‚ÌÄ¶”{—¦
	float stoppedPlayRatio;  // ’â~’†‚ÌÄ¶”{—¦
};

// json‚É©“®•ÏŠ·‚·‚éŠÖ”ŒQ
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
