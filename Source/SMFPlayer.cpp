#include "SMFPlayer.h"

SMFPlayer::SMFPlayer(const fs::path& _file) : GameObject
{
	[](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
				.EndSetter()
		.Build();
	}
},
	file_{ _file }
{
}

SMFPlayer::~SMFPlayer()
{
}

void SMFPlayer::Init()
{
	
}

void SMFPlayer::Update()
{
}

void SMFPlayer::Release()
{
}
