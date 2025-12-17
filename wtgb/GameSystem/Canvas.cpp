#include "pch\pch.h"
#include "Canvas.h"
#include "GameSystem/GameWindow.h"
#include "GameSystem/Direct3D.h"
#include "CPMeshRenderer.h"
#include "Canvas/CanvasContext.h"
#include "Canvas/LayoutConfig.h"
#include "Canvas/RenderContent.h"

wtgb::Canvas::Canvas() :
	context_{ this },
	mesh2D_{},
	system_{ nullptr },
	pReferenceLayoutConfig_{ nullptr }
{
}

wtgb::Canvas::~Canvas()
{
}

wtgb::Result wtgb::Canvas::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	
	mesh2D_.CallInit(system_);
	context_.CallInit(system_);

	return Result::Code::Ok;
}

void wtgb::Canvas::Update(const ViewerUpdate& _system)
{
	using namespace UI;


	CPMeshRenderer& meshRenderer{ _system.Get<CPMeshRenderer>() };
	Direct3D& direct3D{ _system.Get<Direct3D>() };

	/*context_.renderOrder_

	meshRenderer.Render();*/

	direct3D.SetUseDepthBuffer(false);
	direct3D.SetBlend(BlendMode::Alpha);

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

	renderOrder_.clear();

	direct3D.SetUseDepthBuffer(true);
	direct3D.SetBlend(BlendMode::None);
}

void wtgb::Canvas::End()
{
	context_.CallRelease(system_);
	mesh2D_.CallRelease(system_);
}
