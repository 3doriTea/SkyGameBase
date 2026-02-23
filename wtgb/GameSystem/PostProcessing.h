#pragma once
#include "pch/pch.h"
#include "Core/IGameSystem.h"
#include "PostProcessing/BackMesh2D.h"
#include "PostProcessing/IPostProcessEffect.h"
#include "PostProcessing/PostProcessingConstant.h"


namespace wtgb
{
	/// <summary>
	/// <para>ポストプロセッシングシステム</para>
	/// <para>後処理グラフィック</para>
	/// </summary>
	class PostProcessing : public IGameSystem
	{
	public:
		PostProcessing();
		~PostProcessing();

		/// <summary>
		/// 更新タイミング
		/// </summary>
		/// <returns>更新タイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

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
		BackMesh2D mesh2d_;
		std::vector<std::unique_ptr<IPostProcessEffect>> effects_;  // 描画エフェクト
	};
}
