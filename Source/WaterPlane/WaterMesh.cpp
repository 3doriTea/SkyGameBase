#include "pch\pch.h"
#include "WaterMesh.h"


WaterMesh::WaterMesh(const Config& _config) :
	points_{ _config.points },
	SIZE_{ _config.verticesCount },
	VERTICES_DISTANCE_{ _config.verticesDistance }
{
}

WaterMesh::~WaterMesh()
{
}

void WaterMesh::Init(ViewerCached _system)
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

	// 頂点をリセットする
	ResetVertices();

	// 頂点バッファを更新する
	UpdateVertexBuffer(_system);
#pragma endregion

#pragma region インデックス
	{
		std::vector<uint32_t> indices{};
		
		// 1面を描画するインデクス
		static const uint32_t INDEX_SET_ARRAY[]{ 0, 1, 4, 4, 1, 5 };
		static const uint32_t INDEX_SET_ARRAY_SIZE{ sizeof(INDEX_SET_ARRAY) / sizeof(uint32_t) };

		// ポリゴン数
		size_t polyCount{ static_cast<size_t>((SIZE_.x - 1) * (SIZE_.y - 1)) };

		for (int y = 0; y < (SIZE_.x - 1); y++)
		{
			for (int x = 0; x < (SIZE_.x - 1); x++)
			{
				for (int i = 0; i < INDEX_SET_ARRAY_SIZE; i++)
				{
					int offset = x + SIZE_.x * y;
					indices.push_back(
						INDEX_SET_ARRAY[i] + offset
					);
				}
			}
		}

		indexCount_ = static_cast<uint32_t>(indices.size());


		ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

		const D3D11_BUFFER_DESC INDEX_DESC
		{
			// 型の大きさ
			.ByteWidth = static_cast<UINT>(sizeof(uint32_t) * indexCount_),
			.Usage = D3D11_USAGE_DEFAULT,                // 変更するか
			.BindFlags = D3D11_BIND_INDEX_BUFFER,        // なんのバッファか
			.CPUAccessFlags = 0,                         // CPUからのアクセスフラグ
			.MiscFlags = 0,                              // その他のフラグ
			.StructureByteStride = 0,
		};
		const D3D11_SUBRESOURCE_DATA INDEX_DATA
		{
			.pSysMem = indices.data(),
			.SysMemPitch = {},
			.SysMemSlicePitch = {},
		};

		hResult = pDevice->CreateBuffer(&INDEX_DESC, &INDEX_DATA, pIndexBuffer_.GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュのインデックスバッファ作成に失敗");
	}
#pragma endregion

	int count{ 0 };
	/*for (auto& index : indices)
	{
		LOGF("{},", index);
		count++;
		if (count % 3 == 0)
		{
			LOGF("\n");
		}
	}*/

#pragma region コンスタントバッファ
	{
		UINT cbSize = static_cast<UINT>(sizeof(ConstantBuffer));
		cbSize = (cbSize + 15u) & ~15u;

		const D3D11_BUFFER_DESC CONSTANT_DESC
		{
			// 型の大きさ
			.ByteWidth = cbSize,
			.Usage = D3D11_USAGE_DYNAMIC,                // 変更するか
			.BindFlags = D3D11_BIND_CONSTANT_BUFFER,     // なんのバッファか
			.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,    // CPUからのアクセスフラグ
			.MiscFlags = 0,                              // その他のフラグ
			.StructureByteStride = 0,
		};

		ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

		hResult = pDevice->CreateBuffer(&CONSTANT_DESC, nullptr, pConstantBuffer_.GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュコンスタントバッファ作成に失敗");
	}
#pragma endregion
}

void WaterMesh::Release(ViewerCached _system)
{
}

void WaterMesh::UpdateVertexBuffer(ViewerCached _system)
{
	if (points_.size() < 2)
	{
		wassert(false && "平面頂点数が2以上でないと描画できない");
		throw - 1;
	}

	for (int y = 0; y < SIZE_.y; y++)
	{
		for (int x = 0; x < SIZE_.x; x++)
		{
			const size_t INDEX{ static_cast<size_t>(y * SIZE_.x + x) };
			vertices_.at(INDEX).position.y = points_.at(INDEX);
		}
	}

	// バッファ作成
	ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
	HRESULT hResult{};

	const D3D11_BUFFER_DESC VERTEX_DESC
	{
		// 型の大きさ
		.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertexCount_),
		.Usage = D3D11_USAGE_DEFAULT,                // 変更するか
		.BindFlags = D3D11_BIND_VERTEX_BUFFER,       // なんのバッファか
		.CPUAccessFlags = 0,                         // CPUからのアクセスフラグ
		.MiscFlags = 0,                              // その他のフラグ
		.StructureByteStride = sizeof(Vertex),
	};
	const D3D11_SUBRESOURCE_DATA VERTEX_DATA
	{
		.pSysMem = vertices_.data(),
		.SysMemPitch = {},
		.SysMemSlicePitch = {},
	};

	hResult = pDevice->CreateBuffer(&VERTEX_DESC, &VERTEX_DATA, pVertexBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ステージメッシュ頂点バッファ作成に失敗");
}

void WaterMesh::ResetVertices()
{
	vertices_.resize(SIZE_.x * SIZE_.y, Vertex{});
	for (int y = 0; y < SIZE_.y; y++)
	{
		for (int x = 0; x < SIZE_.x; x++)
		{
			const size_t INDEX{ static_cast<size_t>(y * SIZE_.x + x) };
			vertices_.at(INDEX) =
			{
				.position =
				{
					x * VERTICES_DISTANCE_.x,
					points_.at(INDEX),
					y * VERTICES_DISTANCE_.y,
				},
				.normal = Vector3::Up(),
				.uv = {}
			};
		}
	}
}
