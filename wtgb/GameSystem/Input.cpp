#include "pch\pch.h"
#include "Input.h"
#include "Input/InputResource.h"


wtgb::Input::Input() :
	pResource_{ new InputResource{} }
{
}

wtgb::Input::~Input()
{
	SAFE_DELETE(pResource_);
}

wtgb::Result wtgb::Input::Init()
{
	return Result::Code::Ok;
}

void wtgb::Input::Update()
{
}

void wtgb::Input::End()
{
}

bool wtgb::Input::InputData::IsKey(const KeyCode _keyCode)
{
	return false;
}

bool wtgb::Input::InputData::IsKeyDown(const KeyCode _keyCode)
{
	return false;
}

bool wtgb::Input::InputData::IsKeyUp(const KeyCode _keyCode)
{
	return false;
}
