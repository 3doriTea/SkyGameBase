#include "Debugger.h"

Debugger::Debugger() :
	GameObject
	{
		[this](GameObjectBuilder& _builder)
		{
			_builder
				.AddComponent<GameObjectProperty>()
					.BeginSetter()
						.name("Debugger")
					.EndSetter()
				.AddComponent<wtgb::Transform>()
			.Build();
		}
	}
{
}

Debugger::~Debugger()
{
}

void Debugger::Init()
{
}

void Debugger::Update()
{
	const auto& input{ System().Get<Input>().Getter() };
	auto& gameTime{ System().Get<GameTime>() };
	if (input.IsKeyDown(KeyCode::T))
	{
		gameTime.SetTimeStopped(true);
	}
	if (input.IsKeyUp(KeyCode::T))
	{
		gameTime.SetTimeStopped(false);
	}

}

void Debugger::Release()
{
}
