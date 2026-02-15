#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// 指定時間後に処理するシステム
	/// </summary>
	class Alarm : public IGameSystem
	{
	private:
		/// <summary>
		/// 指定時間後の処理ペア
		/// </summary>
		struct AlarmPair
		{
			float timeLeft;                  // カウントダウンタイマー
			std::function<void()> callback;  // 処理
		};

	public:
		Alarm();
		~Alarm();

		/// <summary>
		/// 更新タイミングを取得する
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システムのビュア</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムのビュア</param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// 指定時間後に起動する処理を登録する
		/// </summary>
		/// <param name="_callback">処理のコールバック</param>
		void Add(const std::function<void()>& _callback, const float _time);
	private:

		HandlerCollection<AlarmPair, ModelHandle> registry_;  // アラームハンドラコレクション
	};
}
