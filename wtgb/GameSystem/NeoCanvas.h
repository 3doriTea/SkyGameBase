#pragma once
#include "pch/pch.h"
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// <para>ゲームシステム: NeoCanvas</para>
	/// <para></para>
	/// </summary>
	class NeoCanvas : public IGameSystem
	{
	public:
		NeoCanvas();
		~NeoCanvas();

		/// <summary>
		/// 更新タイミング
		/// </summary>
		/// <returns>更新タイミング</returns>
		const CallType GetCallType() override { return CallType::DoNotUpdate; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システム参照</param>
		/// <returns>初期化処理の結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_viewer">システム参照</param>
		void Update(const ViewerUpdate& _viewer) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		
	};
}
