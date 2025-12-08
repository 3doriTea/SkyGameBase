#include "pch\pch.h"
#include "Canvas.h"
#include "CPMeshRenderer.h"
#include "Canvas/CanvasContext.h"
#include "Canvas/LayoutConfig.h"
#include "Canvas/RenderContent.h"

wtgb::Canvas::Canvas() :
	context_{ this },
	mesh2D_{}
{
}

wtgb::Canvas::~Canvas()
{
}

wtgb::Result wtgb::Canvas::Init(const ViewerInit& _viewer)
{
	mesh2D_.CallInit(_viewer.GetCache());
	return Result::Code::Ok;
}

void wtgb::Canvas::Update(const ViewerUpdate& _system)
{
	using namespace UI;

	CPMeshRenderer& meshRenderer{ _system.Get<CPMeshRenderer>() };

	/*context_.renderOrder_

	meshRenderer.Render();*/


	for (auto& [config, contentVar] : renderOrder_)
	{
		std::visit([&config, &meshRenderer](const auto& content)
			{
				content.Render();
				meshRenderer.Render()
			}, contentVar);
	}
}

void wtgb::Canvas::End()
{
	mesh2D_.CallRelease(System());
}
