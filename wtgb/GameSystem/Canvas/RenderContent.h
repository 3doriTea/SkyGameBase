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

	struct RenderContentImage
	{
		TextureHandle hTexture_;  // テクスチャハンドル
		float angle_;  // 回転角度
		RectF cut_;
		Vector2Int imageSize_;  // 画像サイズ
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

		inline RenderContent<Type>& operator=(const RenderContent<Type>& _other)
			requires (Type == RenderContentType::Image) :
			image{ _other.image },
			hShader2D_{ _other.hShader2D_ }
		{}

		inline RenderContent<Type>& operator=(const RenderContent<Type>& _other)
			requires (Type == RenderContentType::Box) :
			box{ _other.box },
			hShader2D_{ _other.hShader2D_ }
		{
		}


		inline RenderContent<Type>& operator=(const RenderContent<Type>& _other)
			requires (Type == RenderContentType::Image)
		{
			hShader2D_ = _other.hShader2D_;
			image = _other.image;
		}

		inline RenderContent<Type>& operator=(const RenderContent<Type>& _other)
			requires (Type == RenderContentType::Box)
		{
			hShader2D_ = _other.hShader2D_;
			box = _other.box;
		}

		void Render(
			const Vector2Int _screenSize,
			const Matrix4x4& _matrixProjection,
			IMeshSimple2D* _pMeshSimple2D,
			CPMeshRenderer& _meshRenderer,
			const LayoutConfig& _layoutConfig) const
			requires (Type == RenderContentType::Image);
		void Render(
			const Vector2Int _screenSize,
			const Matrix4x4& _matrixProjection,
			IMeshSimple2D* _pMeshSimple2D,
			CPMeshRenderer& _meshRenderer,
			const LayoutConfig& _layoutConfig) const
			requires (Type == RenderContentType::Box);

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
