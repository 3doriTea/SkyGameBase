#include "../CPMeshRenderer.h"
#include "LayoutConfig.h"

namespace wtgb::UI
{
	template<RenderContentType Type>
	inline void UI::RenderContent<Type>::Render(
		CPMeshRenderer& _meshRenderer,
		const LayoutConfig& _layoutConfig) const
		requires (Type == RenderContentType::Image)
	{
		_meshRenderer.Render2D();
	}

	template<RenderContentType Type>
	inline void UI::RenderContent<Type>::Render(
		CPMeshRenderer& _meshRenderer,
		const LayoutConfig& _layoutConfig) const
		requires (Type == RenderContentType::Box)
	{
	}
}
