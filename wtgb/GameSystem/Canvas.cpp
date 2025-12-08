#include "pch\pch.h"
#include "Canvas.h"
#include "GameSystem/GameWindow.h"
#include "CPMeshRenderer.h"
#include "Canvas/CanvasContext.h"
#include "Canvas/LayoutConfig.h"
#include "Canvas/RenderContent.h"

wtgb::Canvas::Canvas() :
	context_{ this },
	mesh2D_{},
	system_{ nullptr }
{
}

wtgb::Canvas::~Canvas()
{
}

wtgb::Result wtgb::Canvas::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	mesh2D_.CallInit(system_);
	return Result::Code::Ok;
}

void wtgb::Canvas::Update(const ViewerUpdate& _system)
{
	using namespace UI;

	CPMeshRenderer& meshRenderer{ _system.Get<CPMeshRenderer>() };

	/*context_.renderOrder_

	meshRenderer.Render();*/

	const Vector2Int SCREEN_SIZE{ _system.Get<GameWindow>().GetMainWindowSize() };
	for (auto& [config, contentVar] : renderOrder_)
	{
		std::visit([this, &config, &meshRenderer, &SCREEN_SIZE](const auto& content)
			{
				content.Render(
					SCREEN_SIZE,
					config.GetProjectionMatrix(SCREEN_SIZE),
					&mesh2D_,
					meshRenderer,
					config);
			}, contentVar);
	}
}

void wtgb::Canvas::End()
{
	mesh2D_.CallRelease(system_);
}
