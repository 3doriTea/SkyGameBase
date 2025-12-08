#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"
#include "CoreType/Handler.h"
#include "ContentAndConfig.h"


namespace wtgb
{
	class Canvas;
}

namespace wtgb::UI
{
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
		/// <param name="_hTexture">テクスチャのハンドル</param>
		/// <param name="_angle">基準点からの回転角度</param>
		void DrawImage(const TextureHandle _hTexture, const float _angle);

		/// <summary>
		/// 四角形を描画する
		/// </summary>
		/// <param name="_color">四角形の塗りつぶし色</param>
		/// <param name="_angle">基準点からの回転角度</param>
		void DrawBox(const Color _color, const float _angle);

	private:
		/// <summary>
		/// 描画要求を追加する
		/// </summary>
		/// <param name="_content">要求する描画内容</param>
		void AddRenderOrder(const RenderContentVT& _content);

	private:
		LayoutConfig currentConfig_;  // 現在の設定
	};
}
