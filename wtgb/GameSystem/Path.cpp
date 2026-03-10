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
	SetCurrentDirectory("./Assets");

	Current::pInstance_ = new Current{ fs::current_path() };
	return Result::Code::Ok;
}

void wtgb::Path::End()
{
	SAFE_DELETE(Current::pInstance_);
}

wtgb::Path::Current::Current(const fs::path& _currentPath) :
	currentPath_{ _currentPath }
{
	wassert(pInstance_ == nullptr && "複数のインスタンスが作られている");
	pInstance_ = this;
}

fs::path wtgb::Path::Current::Directory()
{
	return fs::current_path();
}

bool wtgb::Path::Current::Exists(const fs::path& _path)
{
	fs::path p{ fs::current_path() };
	return fs::exists(_path);
}

wtgb::Path::Current* wtgb::Path::Current::pInstance_{ nullptr };
