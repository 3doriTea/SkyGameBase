#include "MapView.h"

MapView::MapView() : GameObject{ "MapView.json" }
{
}

MapView::~MapView()
{
}

void MapView::OnLoadParam(const json& _json)
{
	mapSizePix_ = static_cast<float>(SafeGet<int>(_json, "mapSizePix"));

	if (_json.contains("mapPoints"))
	{
		mapPoints_.resize(_json.array().size());
		size_t i{ 0 };
		for (json& point : _json.array())
		{
			mapPoints_.at(i) = SafeGet<Vector2Int>(_json, "mapPoints");
			i++;
		}
	}

}

void MapView::Init()
{
	OnLoadParam(GetComponent<Parameter>().Load());
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

	//context.DrawImage()
}

void MapView::Release()
{
}
