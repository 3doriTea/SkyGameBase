#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"
#include "CoreType/Handler.h"
#include "RenderContent.h"

namespace wtgb::UI
{
	class Canvas;

	/// <summary>
	/// UI描画へのアクセス
	/// </summary>
	class CanvasContext : public Accessor<Canvas>
	{
	public:
		using Accessor<Canvas>::Accessor;
		~CanvasContext() {}

		/// <summary>
		/// レイアウトのセットをする
		/// </summary>
		/// <param name="_config">レイアウト設定</param>
		void SetLayout(const LayoutConfig& _config);

		/// <summary>
		/// 画像の描画をする
		/// </summary>
		/// <param name="_position">描画基準座標</param>
		/// <param name="_hTexture">テクスチャのハンドル</param>
		void DrawImage(const TextureHandle _hTexture);

	private:
		void AddRenderOrder(const RenderContentVT& _content);

	private:
		LayoutConfig currentConfig_;  // 現在の設定

		std::vector<std::tuple<LayoutConfig, RenderContentVT>> renderOrder_;  // 描画オーダー
	};
}
