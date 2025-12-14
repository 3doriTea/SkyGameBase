#include "pch/pch.h"
#include "Piano.h"

using namespace wtgb;

Piano::Piano() : GameObject
{
	[](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("Piano")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
				.EndSetter()
		.Build();
	}
}
{
}

Piano::~Piano()
{
}

void Piano::Init()
{
	Audio& audio{ System().Get<Audio>() };
	hTestAudio_ = audio.Load("Sound/maou_se_inst_piano2_1do.mp3");
}

void Piano::Update()
{
	Audio& audio{ System().Get<Audio>() };
	const Input::InputGetter& input{ System().Get<Input>().Getter() };

	if (input.IsKeyDown(KeyCode::F))
	{
		audio.Play(hTestAudio_);
	}
}

void Piano::Release()
{
}
