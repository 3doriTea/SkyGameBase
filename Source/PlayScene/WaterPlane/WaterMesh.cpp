#include "pch\pch.h"
#include "WaterMesh.h"

WaterMesh::WaterMesh(ViewerCached _system, WavePoints& _points, const Vector2Int _size) :
	system_{ _system },
	points_{ _points },
	SIZE_{ _size }
{
}

WaterMesh::~WaterMesh()
{
}

void WaterMesh::Init()
{
	using namespace DirectX;

	wassert(SIZE_.x > 0 && SIZE_.y > 0);

	// 面の数
	uint32_t faceCount{ static_cast<uint32_t>((SIZE_.x - 1) * (SIZE_.y - 1)) };

	// 三角形の数 = 面の2倍
	uint32_t polyCount{ faceCount * 2 };

#pragma region 頂点
	// 頂点数
	vertexCount_ = SIZE_.x * SIZE_.y;

	// 頂点をポイントとして更新する
	UpdateWaveVertex();
#pragma endregion

#pragma region インデックス
	
	for (int i = 0; i < indexCount_; i++)
	{
		
	}
#pragma endregion

#pragma region コンスタントバッファ

#pragma endregion
}

void WaterMesh::Release()
{
}

void WaterMesh::UpdateWaveVertex()
{
	// 頂点ず
	vertices.resize(SIZE_.x * SIZE_.y, Vertex{});

	for (int y = 0; y < SIZE_.y; y++)
	{
		for (int x = 0; x < SIZE_.x; x++)
		{
			Vertex v
			{
				//.normal =
			};
			points_[y * SIZE_.x + x];
		}
	}
}
