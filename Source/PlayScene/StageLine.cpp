#include "pch\pch.h"
#include "StageLine.h"

using namespace wtgb;

StageLine::StageLine() : GameObject
{
	[this](GameObjectBuilder& _builder)
	{
		_builder
			.AddComponent<GameObjectProperty>()
				.BeginSetter()
					.name("StageLine")
				.EndSetter()
			.AddComponent<wtgb::Transform>()
				.BeginSetter()
				.EndSetter()
			.AddComponent<ModelMesh>()
				.BeginSetter()
					.pOriginalMesh(&this->stageMesh_)
				.EndSetter()
			.AddComponent<MeshRenderer>()
			.BeginSetter()
				.shader("Shader/StageMesh.hlsl")
			.EndSetter()
		.Build();
	}
},
	stageMesh_{ System(), points_ }
{
}

StageLine::~StageLine()
{
}

void StageLine::Init()
{
	/*points_ =
	{
		{ 0, 0 },
		{ 80, 40 },
		{ 120, 80 },
		{ 200, 120 },
		{ 240, 180 },
		{ 310, 180 },
		{ 350, 210 },
		{ 430, 310 },
		{ 620, 320 },
	};*/

	points_ = 
	{
		{ 3, 2 },
		{ 5, 2 },
	};

	// ‘S‚Ä‚Ì y Ž²‚ð - ‚É‚·‚é
	for (auto& point : points_)
	{
		point.y = -point.y;
	}

	stageMesh_.CallInit();
}

void StageLine::Update()
{
	//stageMesh_.CallRelease();
}

void StageLine::Release()
{
	stageMesh_.CallRelease();
}
