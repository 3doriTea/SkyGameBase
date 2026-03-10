#pragma once
#include <cstdint>

struct Note
{
	Note() :
		Note{ 0.0f, 0, 0, 0 }
	{
	}
	Note(
		float _totalTime,
		uint8_t _channel,
		uint8_t _noteNumber,
		uint8_t _velocity) :
		totalTime{ _totalTime },
		channel{ _channel },
		noteNumber{ _noteNumber },
		velocity{ _velocity }
	{
	}
	float totalTime;     // 絶対的な時間
	float playTime;      // 再生時間
	//float diffTime;    // 前回のノーツとの相対的な時間
	uint8_t channel;     // チャンネル
	uint8_t noteNumber;  // 音の高さ
	uint8_t velocity;    // 音の強さ
};
