#pragma once
#include "pch/pch.h"
#include "UniqueXAudio2SourceVoice.h"

namespace wtgb
{
	using SourceVoiceIndex = int32_t;

	class Audio;

	/// <summary>
	/// 音声再生するやつ
	/// </summary>
	class AudioPlayer
	{
		struct AudioEntry
		{
			AudioEntry(const float _timeLeft, AudioPlayer& _audioPlayer, const SourceVoiceIndex _sourceVoiceIndex);
			~AudioEntry();

			float timeLeft;              // 残りの再生時間
			SourceVoiceIndex sourceVoiceIndex;  // 使っている再生機のインデクス
			AudioPlayer& audioPlayer;  // 再生するやつへの参照
		};

	public:
		AudioPlayer();
		~AudioPlayer();

		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_dt">フレーム間時間</param>
		void Update(const float _dt);

		/// <summary>
		/// 再生キューをクリアする
		/// </summary>
		void Clear();

		/// <summary>
		/// 再生する
		/// </summary>
		/// <param name="_buffer">再生するバッファ</param>
		/// <param name="_format">再生するフォーマット</param>
		/// <param name="_audioSystem">音声システムの参照</param>
		SourceVoiceIndex Play(
			const float _playTimeSec,
			const XAUDIO2_BUFFER& _buffer,
			const WAVEFORMATEX& _format,
			Audio& _audioSystem);

	private:
		void InsertEntryQueue(float _timeLeft, const SourceVoiceIndex _index);

	private:
		// 音声再生機
		std::vector<UniqueXAudio2SourceVoice> sourceVoices_;
		std::vector<bool> useFlag_;  // 再生機の使用フラグ

		std::list<AudioEntry> entryQueue_;  // 再生キュー
	};
}
