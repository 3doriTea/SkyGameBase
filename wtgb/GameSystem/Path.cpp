#include "pch\pch.h"
#include "Path.h"
#include "WTGBAssert.h"

wtgb::Path::Path()
{
}

wtgb::Path::~Path()
{
}

wtgb::Result wtgb::Path::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Path::End()
{
}

wtgb::Path::Current::Current()
{
	wassert(pInstance_ != nullptr);
	pInstance_ = this;
}

wtgb::Path::Current* wtgb::Path::Current::pInstance_{ nullptr };
