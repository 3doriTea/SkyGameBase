#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// 音声再生するやつ
	/// </summary>
	class AudioPlayer
	{
		struct AudioEntry
		{
			AudioEntry();
			~AudioEntry();

			float timeLeft;              // 残りの再生時間
			uint32_t sourceVoiceIndex_;  // 使っている再生機のインデクス
		};

	public:
		AudioPlayer();
		~AudioPlayer();

		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_dt">フレーム間時間</param>
		void Update(const float _dt);

	private:
		// 音声再生機
		std::vector<ComPtr<IXAudio2SourceVoice>> sourceVoices_;
		std::vector<bool> useFlag_;  // 再生機の使用フラグ
	};
}
