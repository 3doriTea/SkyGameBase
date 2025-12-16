#pragma once
#include "Core/IGameSystem.h"
#include "Audio/AudioPlayer.h"
#include "Audio/AudioClip.h"
#include "Audio/UniqueXAudio2MasteringVoice.h"

namespace wtgb
{
	class Audio : public IGameSystem
	{
	public:
		Audio();
		~Audio();

		/// <summary>
		/// 更新の呼び出しタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// 音声再生するやつを作成する
		/// </summary>
		/// <param name="_ppSourceVoice">作成先のポインタ</param>
		/// <param name="_format">フォーマット</param>
		void CreateSourceVoice(IXAudio2SourceVoice** _ppSourceVoice, const WAVEFORMATEX& _format);
		/// <summary>
		/// 音声を予め読み込んでおく
		/// </summary>
		/// <param name="_audioFileName">音声ファイルパス</param>
		[[nodiscard]]
		AudioHandle Load(const fs::path& _audioFileName);
		/// <summary>
		/// 予め読み込んだ音声を再生
		/// </summary>
		/// <param name="_hAudio">音声のハンドル</param>
		/// <param name="_time">再生時間</param>
		/// <param name="_samplePerSec">サンプリング周波数</param>
		void Play(const AudioHandle _hAudio, const float _time = 0.0f, const unsigned long _samplePerSec = 0);
		/// <summary>
		/// 即読み込んで再生する
		/// </summary>
		/// <param name="_audioFileName">音声ファイルパス</param>
		void PlayOneShot(const fs::path& _audioFileName);

		/// <summary>
		/// 読み込んだフォーマットを取得する
		/// </summary>
		/// <returns>読み込んだフォーマット</returns>
		WAVEFORMATEX GetFormat(const AudioHandle _hAudio) const;

	private:
		ComPtr<IXAudio2> pXAudio2_;  // XAudio2本体のインタフェース
		UniqueXAudio2MasteringVoice pMasteringVoice_;  // 主音声
		AudioPlayer audioPlayer_;  // 音声再生するやつ
		HandlerCollection<AudioClip, AudioHandle> audioClips_;  // クリップのハンドルコレクション
	};
}
