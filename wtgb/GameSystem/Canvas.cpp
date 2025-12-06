#include "pch\pch.h"
#include "Canvas.h"
#include "CPMeshRenderer.h"

wtgb::Canvas::Canvas() :
	context_{ this }
{
}

wtgb::Canvas::~Canvas()
{
}

wtgb::Result wtgb::Canvas::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Canvas::Update(const ViewerUpdate& _system)
{
	CPMeshRenderer& meshRenderer{ _system.Get<CPMeshRenderer>() };

	/*context_.renderOrder_

	meshRenderer.Render();*/
}

void wtgb::Canvas::End()
{
}
