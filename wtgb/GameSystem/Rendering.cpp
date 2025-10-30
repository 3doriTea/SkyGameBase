#include "pch\pch.h"
#include "Rendering.h"
#include "CPGameObject.h"
#include "Direct3D.h"

wtgb::Rendering::Rendering()
{
}

wtgb::Rendering::~Rendering()
{
}

wtgb::Result wtgb::Rendering::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Rendering::Update(const ViewerUpdate& _system)
{
	_system.Get<CPGameObject>().Draw();
	_system.Get<Direct3D>().Render();
}

void wtgb::Rendering::End()
{
}
