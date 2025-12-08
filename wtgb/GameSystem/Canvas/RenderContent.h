#pragma once
#include <variant>
#include "pch/pch.h"

namespace wtgb
{
	class CPMeshRenderer;
	class LayoutConfig;
}

namespace wtgb::UI
{
	enum struct RenderContentType
	{
		Image,  // 画像の描画
		Box,    // 四角形の描画
	};

	struct RenderContentImage
	{
		TextureHandle hTexture_;  // テクスチャハンドル
		float angle_;  // 回転角度
	};

	struct RenderContentBox
	{
		Color color;  // 色
		float angle_;  // 回転角度
	};

	/// <summary>
	/// 描画する内容
	/// </summary>
	template<RenderContentType Type>
	class RenderContent
	{
	public:
		RenderContent(const TextureHandle _hTexture, float _angle)
			requires (Type == RenderContentType::Image) :
			image{ .hTexture_ = _hTexture, .angle_ = _angle }
		{
		}

		RenderContent(const Color _color, float _angle)
			requires (Type == RenderContentType::Box) :
			box{ .color = _color, .angle_ = _angle }
		{
		}

		void Render(CPMeshRenderer& _meshRenderer, const LayoutConfig& _layoutConfig) const requires (Type == RenderContentType::Image);
		void Render(CPMeshRenderer& _meshRenderer, const LayoutConfig& _layoutConfig) const requires (Type == RenderContentType::Box);

	private:
		union
		{
			RenderContentImage image;  // 画像
			RenderContentBox box;      // 四角形
		};

		ShaderHandle hShader2D_;  // 描画用シェーダのハンドル
	};

	/// <summary>
	/// 描画内容の共通型
	/// </summary>
	using RenderContentVT = std::variant<
		RenderContent<RenderContentType::Image>,
		RenderContent<RenderContentType::Box>>;
}

#include "RenderContent.inl"
