#pragma once
#include "GameSystem/CPMeshRenderer.h"
#include "LayoutConfig.h"

namespace wtgb::UI
{
	/// <summary>
	/// 描画内容のインタフェース
	/// </summary>
	struct IRenderContent
	{
		IRenderContent() = default;
		virtual ~IRenderContent() = default;
		
		/// <summary>
		/// 描画処理
		/// </summary>
		virtual void Render(
			const Vector2Int _screenSize,
			const Matrix4x4& _matrixProjection,
			IMeshSimple2D* _pMeshSimple2D,
			CPMeshRenderer& _meshRenderer,
			const LayoutConfig& _layoutConfig) const = 0;
	};
}
