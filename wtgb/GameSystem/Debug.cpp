#include "pch\pch.h"
#include "Debug.h"

#include "Core/Game.h"
#include "Input.h"

//#include "ResourceSystem/Texture.h"
#include "ResourceSystem.h"

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

	if (input.IsKeyDown(KeyCode::L))
	{
		TextureHandle hTexture = _system.Get<ResourceSystem>().LoadTexture("Assets/Model/Oden.jpg");

		LOGFLN("ì«Ç›çûÇÒÇæÅI{}", hTexture);

	}
}

void wtgb::Debug::End()
{
}
