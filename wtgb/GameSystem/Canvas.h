#pragma once
#include "Core/IGameSystem.h"
#include "Canvas/Mesh2D.h"
#include "Canvas/CanvasContext.h"
#include "Canvas/ContentAndConfig.h"

namespace wtgb
{
	/// <summary>
	/// UI表示用キャンバスシステム
	/// </summary>
	class Canvas : public IGameSystem
	{
		friend class wtgb::UI::CanvasContext;
	
	public:
		using Context = wtgb::UI::CanvasContext;
		using LayoutConfig = wtgb::UI::LayoutConfig;
	
	public:
		Canvas();
		~Canvas();

		/// <summary>
		/// 更新のタイミングを取得する
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// キャンバスへの描画用コンテキストを取得
		/// </summary>
		/// <returns>描画用コンテキスト</returns>
		const UI::CanvasContext& GetContext() const { return context_; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_viewer">システムアクセス用</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムアクセス用</param>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		Mesh2D mesh2D_;
		ViewerCached system_;

		UI::LayoutConfig* pReferenceLayoutConfig_;  // 現在の参照レイアウト設定

		UI::CanvasContext context_;  // キャンバスアクセス用コンテキスト
		std::vector<UI::ContentAndConfig> renderOrder_;  // 描画オーダー
	};
}

