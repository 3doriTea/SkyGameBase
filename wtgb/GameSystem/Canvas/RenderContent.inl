#include "../CPMeshRenderer.h"
#include "LayoutConfig.h"
#include "RenderContent.h"

namespace wtgb::UI
{
	template<RenderContentType Type>
	inline void UI::RenderContent<Type>::Render(
		const Vector2Int _screenSize,
		const Matrix4x4& _matrixProjection,
		IMeshSimple2D* _pMeshSimple2D,
		CPMeshRenderer& _meshRenderer,
		const LayoutConfig& _layoutConfig) const
		requires (Type == RenderContentType::Image)
	{
		using namespace DirectX;
#pragma region UV計算
		// トリミング計算

		const Vector2 CUT_BEGIN{ image.cut_.GetBegin() };
		const Vector2 CUT_END{ image.cut_.GetEnd() };

		// トリミング矩形の左上点を並行移動
		Matrix4x4 uvMove = XMMatrixTranslation(
			CUT_BEGIN.x * 1.0f / image.imageSize_.x,
			CUT_BEGIN.y * 1.0f / image.imageSize_.y,
			0.0f);

		// トリミング矩形の拡縮
		Matrix4x4 uvScaling = XMMatrixScaling(
			static_cast<float>(CUT_END.x) / image.imageSize_.x,
			static_cast<float>(CUT_END.y) / image.imageSize_.y,
			1.0f);

		// uv 行列
		Matrix4x4 matrixUV{ XMMatrixTranspose(uvScaling * uvMove) };
#pragma endregion

		_meshRenderer.Render2D(
			_pMeshSimple2D,
			_matrixProjection,
			matrixUV,
			hShader2D_,
			Color::GREEN,
			image.hTexture_);
	}

	template<RenderContentType Type>
	inline void UI::RenderContent<Type>::Render(
		const Vector2Int _screenSize,
		const Matrix4x4& _matrixProjection,
		IMeshSimple2D* _pMeshSimple2D,
		CPMeshRenderer& _meshRenderer,
		const LayoutConfig& _layoutConfig) const
		requires (Type == RenderContentType::Box)
	{
		using namespace DirectX;

		_meshRenderer.Render2D(
			_pMeshSimple2D,
			_matrixProjection,
			XMMatrixIdentity(),
			hShader2D_,
			box.color);
	}
}
