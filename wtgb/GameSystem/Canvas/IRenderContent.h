#pragma once
#include "GameSystem/CPMeshRenderer.h"
#include "LayoutConfig.h"

namespace wtgb::UI
{
	/// <summary>
	/// 描画内容のインタフェース
	/// </summary>
	class IRenderContent
	{
	public:
		IRenderContent() {}
		virtual ~IRenderContent() {}

		virtual void Render(CPMeshRenderer& _meshRenderer, const LayoutConfig& _layoutConfig) const = 0;
	};
}
