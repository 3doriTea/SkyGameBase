#pragma once
#include <variant>
#include "pch/pch.h"
#include "IRenderContent.h"

namespace wtgb
{
	class CPMeshRenderer;
	class LayoutConfig;
	class IMeshSimple2D;
}

namespace wtgb::UI
{
	enum struct RenderContentType
	{
		Image,  // 画像の描画
		Box,    // 四角形の描画
	};

	struct RenderContentImage : IRenderContent
	{
		RenderContentImage(
			const TextureHandle _hTexture,
			const float _angle,
			const RectF& _cut,
			const Vector2Int _imageSize,
			const ShaderHandle _hShader);
		~RenderContentImage() {}

		void Render(
			const Vector2Int _screenSize,
			const Matrix4x4& _matrixProjection,
			IMeshSimple2D* _pMeshSimple2D,
			CPMeshRenderer& _meshRenderer,
			const LayoutConfig& _layoutConfig) const override;

		TextureHandle hTexture;  // テクスチャハンドル
		float angle;  // 回転角度
		RectF cut;
		Vector2Int imageSize;  // 画像サイズ
		ShaderHandle hShader;  // シェーダハンドル
	};

	struct RenderContentBox : IRenderContent
	{
		RenderContentBox(
			const Color& _color,
			const float _angle,
			const ShaderHandle _hShader);
		~RenderContentBox() {}

		void Render(
			const Vector2Int _screenSize,
			const Matrix4x4& _matrixProjection,
			IMeshSimple2D* _pMeshSimple2D,
			CPMeshRenderer& _meshRenderer,
			const LayoutConfig& _layoutConfig) const override;

		Color color;           // 色
		float angle;           // 回転角度
		ShaderHandle hShader;  // シェーダハンドル
	};

	
	/// <summary>
	/// 描画内容の共通型
	/// </summary>
	using RenderContentVT = std::variant<
		RenderContentBox,
		RenderContentImage>;
}

#include "RenderContent.inl"
