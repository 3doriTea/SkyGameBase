#include "pch\pch.h"
#include "CPMeshRenderer.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/Model.h"

wtgb::CPMeshRenderer::CPMeshRenderer()
{
}

wtgb::CPMeshRenderer::~CPMeshRenderer()
{
}

void wtgb::CPMeshRenderer::Init()
{
}

void wtgb::CPMeshRenderer::Update()
{
	for (auto itr = this->begin(); itr != this->end(); itr++)
	{
		size_t index{ itr - this->end() };
		EntityId entityId{ System().Get<CPGameObject>().GetEntityId(index) };
		ModelHandle hModel{ System().Get<CPModelMesh>().Get(entityId)->hModel_ };

		System().Get<Model>().
	}
}
