#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// 描画を司るシステム
	/// </summary>
	class Rendering : public IGameSystem
	{
	public:
		Rendering();
		~Rendering();

		/// <summary>
		/// 更新タイミングを取得する
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">他システムのアクセッサ</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">他システムのアクセッサ</param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;
	};
}
