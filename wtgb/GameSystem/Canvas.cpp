#include "pch\pch.h"
#include "Canvas.h"

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
}

void wtgb::Canvas::End()
{
}
