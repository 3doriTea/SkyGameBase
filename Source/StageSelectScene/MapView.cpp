#include "MapView.h"

MapView::MapView() : GameObject{ "MapView.json" }
{
}

MapView::~MapView()
{
}

void MapView::Init()
{
}

void MapView::Update()
{
	using namespace UI;

	const Canvas::Context& context{ System().Get<Canvas>().GetContext() };

	Canvas::LayoutConfig layoutConfig
	{
		Canvas::LayoutConfig{}
			.position({})
			.scale({})
	};
	context.SetRefLayout(&layoutConfig);

	context.DrawImage()
}

void MapView::Release()
{
}
