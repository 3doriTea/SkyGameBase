#pragma once
#include "Core/IGameSystem.h"

#pragma comment(lib, "Winmm.lib")  // timeBeginPeriodと timeEndPeriodで必要

// LARGE_INTEGER の前方宣言
typedef union _LARGE_INTEGER LARGE_INTEGER;

namespace wtgb
{
	class GameTime : public IGameSystem
	{
	public:
		GameTime();
		~GameTime();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		inline const CallType GetCallType() override { return CallType::Cycle; }

		/// <summary>
		/// フレーム間時間を取得する
		/// </summary>
		/// <returns></returns>
		const float GetDeltaTime() const { return deltaTimeSec_; }
		/// <summary>
		/// フレームが切り替わるタイミングかどうか
		/// </summary>
		/// <returns>切り替わるタイミング true / false</returns>
		const bool IsFrameDue() const { return isFrameDue_; }

		/// <summary>
		/// 時間を止めるか
		/// </summary>
		/// <param name="_timeStopped">時間を止める true / false</param>
		void SetTimeStopped(const bool _timeStopped);
		
		/// <summary>
		/// 時間の大きさを決める
		/// </summary>
		/// <param name="_timeScale">時間の大きさ</param>
		void SetTimeScale(const float _timeScale);

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

	private:
		bool isFrameDue_;  // フレームが切り替わるタイミング true / false
		float deltaTimeSec_;  // フレーム間時間
		float timeScalePrev_;  // 前回設定したゲーム内時間の大きさ
		float timeScale_;      // ゲーム内時間の大きさ
		LARGE_INTEGER currentMicro_;  // 現在のCPU時間 (マイクロ秒)
		LARGE_INTEGER previousMicro_;  // 前回のCPU時間 (マイクロ秒)
	private:
		static const UINT PERIOD_MILLI;  // 分解能(ミリ秒)
		static const LONGLONG ONE_SEC_TO_MICRO;  // 1秒はマイクロ秒で表すと
		static const float MICRO_TO_SEC;  // マイクロ秒を秒に変換する
	};
}
