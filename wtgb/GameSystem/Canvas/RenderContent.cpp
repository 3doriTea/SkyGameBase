#include "pch\pch.h"
#include "RenderContent.h"

wtgb::UI::RenderContentBox::RenderContentBox(
	const Color& _color,
	const float _angle,
	const ShaderHandle _hShader) :
	color{ _color },
	angle{ _angle },
	hShader{ _hShader }
{
}

void wtgb::UI::RenderContentBox::Render(
	const Vector2Int _screenSize,
	const Matrix4x4& _matrixProjection,
	IMeshSimple2D* _pMeshSimple2D,
	CPMeshRenderer& _meshRenderer,
	const LayoutConfig& _layoutConfig) const
{
	using namespace DirectX;

	_meshRenderer.Render2D(
		_pMeshSimple2D,
		_matrixProjection,
		XMMatrixIdentity(),
		hShader,
		alpha,
		color);
}

wtgb::UI::RenderContentImage::RenderContentImage(
	const TextureHandle _hTexture,
	const float _angle,
	const RectF& _cut,
	const Vector2Int _imageSize,
	const ShaderHandle _hShader) :
	hTexture{ _hTexture },
	angle{ _angle },
	cut{ _cut },
	imageSize{ _imageSize },
	hShader{ _hShader }
{
}

void wtgb::UI::RenderContentImage::Render(
	const Vector2Int _screenSize,
	const Matrix4x4& _matrixProjection,
	IMeshSimple2D* _pMeshSimple2D,
	CPMeshRenderer& _meshRenderer,
	const LayoutConfig& _layoutConfig) const
{
	{
		using namespace DirectX;
#pragma region UV計算
		// トリミング計算

		const Vector2 CUT_BEGIN{ cut.GetBegin() };
		const Vector2 CUT_END{ cut.GetEnd() };

		Matrix4x4 uvRotate = XMMatrixRotationZ(angle);

		// トリミング矩形の左上点を並行移動
		Matrix4x4 uvMove = XMMatrixTranslation(
			CUT_BEGIN.x * 1.0f / imageSize.x,
			CUT_BEGIN.y * 1.0f / imageSize.y,
			0.0f);

		// トリミング矩形の拡縮
		Matrix4x4 uvScaling = XMMatrixScaling(
			static_cast<float>(CUT_END.x - CUT_BEGIN.x) / imageSize.x,
			static_cast<float>(CUT_END.y - CUT_BEGIN.y) / imageSize.y,
			1.0f);

		// uv 行列
		Matrix4x4 matrixUV{ XMMatrixTranspose(uvScaling * uvRotate * uvMove) };
#pragma endregion

		_meshRenderer.Render2D(
			_pMeshSimple2D,
			_matrixProjection,
			matrixUV,
			hShader,
			alpha,
			Color::GREEN,
			hTexture);
	}
}
