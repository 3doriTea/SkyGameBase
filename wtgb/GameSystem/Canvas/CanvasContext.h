#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"
#include "CoreType/Handler.h"
#include "ContentAndConfig.h"
#include "Utility/IResource.h"


namespace wtgb
{
	class Canvas;
	class ResourceSystem;
}

namespace wtgb::UI
{
	/// <summary>
	/// UI描画へのアクセス
	/// </summary>
	class CanvasContext : public Accessor<Canvas>, public IResource<ViewerCached>
	{
	public:
		CanvasContext(Canvas* _pCanvas);
		~CanvasContext() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_system">システムアクセス</param>
		void Init(ViewerCached _system) override;
		/// <summary>
		/// 解放処理
		/// </summary>
		/// <param name="_system">システムアクセス</param>
		void Release(ViewerCached _system) override;

		/// <summary>
		/// レイアウトのセットをする
		/// </summary>
		/// <param name="_config">レイアウト設定</param>
		void SetLayout(const LayoutConfig& _config) const;

		/// <summary>
		/// 画像の描画をする
		/// </summary>
		/// <param name="_hTexture">テクスチャのハンドル</param>
		/// <param name="_angle">基準点からの回転角度</param>
		void DrawImage(const TextureHandle _hTexture, const float _angle = 0.0f, const RectF& _cut = {}) const;

		/// <summary>
		/// 四角形を描画する
		/// </summary>
		/// <param name="_color">四角形の塗りつぶし色</param>
		/// <param name="_angle">基準点からの回転角度</param>
		void DrawBox(const Color _color, const float _angle = 0.0f) const;

	private:
		/// <summary>
		/// 描画要求を追加する
		/// </summary>
		/// <param name="_content">要求する描画内容</param>
		void AddRenderOrder(const RenderContentVT& _content) const;

	private:
		LayoutConfig currentConfig_;  // 現在の設定

		ViewerCached system_;  // システムへのアクセス用
		ShaderHandle hBoxShader_;    // ボックス描画用シェーダ
		ShaderHandle hImageShader_;  // 画像描画用シェーダ
	};
}
