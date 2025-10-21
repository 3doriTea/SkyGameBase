#include "pch\pch.h"
#include "Debug.h"

#include "Input.h"

wtgb::Debug::Debug()
{
}

wtgb::Debug::~Debug()
{
}

wtgb::Result wtgb::Debug::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Debug::Update(const ViewerUpdate& _system)
{
	Vector2Int mousePos{  _system.Get<Input>().Getter().GetMouseMove() };
	LOGF("{}, {}\n", mousePos.x, mousePos.y);
}

void wtgb::Debug::End()
{
}
