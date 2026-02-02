#include "WaterPool.h"

WaterPool::WaterPool() :
	GameObject{ "Simple.json" },
	waterMesh_
	{
		WaterMesh::Config
		{
			.points = points_,
			.verticesCount = { 30, 30 },
			.verticesDistance = { 10.0f, 10.0f },
		}
	}
	//waterMesh_{  }
{
}

WaterPool::~WaterPool()
{
}

void WaterPool::Init()
{
}

void WaterPool::Update()
{
}

void WaterPool::Release()
{
}

void WaterPool::OnLoadParam(const json& _json)
{
	//_json
}
