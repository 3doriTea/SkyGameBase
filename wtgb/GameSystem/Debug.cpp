#include "pch\pch.h"
#include "Debug.h"

#include "Core/Game.h"
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
	Input::InputGetter input{ _system.Get<Input>().Getter() };

	Vector2Int mousePos{ input.GetMouseMove() };
	LOGF("{}, {}\n", mousePos.x, mousePos.y);

	if (input.IsKey(KeyCode::G))
	{
		static int count{};
		count++;
		if (count >= 3)
		{
			Game::Exit();
		}
	}
}

void wtgb::Debug::End()
{
}
