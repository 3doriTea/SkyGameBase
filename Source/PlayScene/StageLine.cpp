#include "pch\pch.h"
#include "StageLine.h"

using namespace wtgb;

StageLine::StageLine() : GameObject(
	{
		[this](GameObjectBuilder& _builder)
		{
			_builder
				.AddComponent<ModelMesh>()
					.BeginSetter()
						.pOriginalMesh(&this->stageMesh_)
					.EndSetter()
				.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/Simple3D.hlsl")
				.EndSetter()
			.Build();
		}
	})
{
}

StageLine::~StageLine()
{
}

void StageLine::Init()
{
	points_ =
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
	};

	// ‘S‚Ä‚Ì y Ž²‚ð - ‚É‚·‚é
	for (auto& point : points_)
	{
		point.y = -point.y;
	}
}

void StageLine::Update()
{
}
