#include "pch\pch.h"
#include "Mesh2D.h"
#include "GameSystem/Direct3D.h"

wtgb::Mesh2D::Mesh2D()
{
}

wtgb::Mesh2D::~Mesh2D()
{
}

void wtgb::Mesh2D::Init(ViewerCached _system)
{
#pragma region 頂点を求める
	{
		// 頂点情報
		Vertex vertices[]
		{
			{ Vector4{ -1,  1 }, Vector4{ 0, 0 } },  // 左上
			{ Vector4{  1,  1 }, Vector4{ 1, 0 } },  // 右上
			{ Vector4{ -1, -1 }, Vector4{ 0, 1 } },  // 左下
			{ Vector4{  1, -1 }, Vector4{ 1, 1 } },  // 右下
		};

		vertexCount_ = static_cast<uint32_t>(sizeof(vertices) / sizeof(Vertex));

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
			.pSysMem = vertices,
			.SysMemPitch = {},
			.SysMemSlicePitch = {},
		};

		hResult = pDevice->CreateBuffer(&VERTEX_DESC, &VERTEX_DATA, pVertexBuffer_.GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュ頂点バッファ作成に失敗");
	}
#pragma endregion

#pragma region インデックス
	{
		const int INDICES[]{ 2, 1, 0, 2, 3, 1 };

		indexCount_ = static_cast<uint32_t>(sizeof(INDICES) / sizeof(uint32_t));


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
			.pSysMem = INDICES,
			.SysMemPitch = {},
			.SysMemSlicePitch = {},
		};

		hResult = pDevice->CreateBuffer(&INDEX_DESC, &INDEX_DATA, pIndexBuffer_.GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュのインデックスバッファ作成に失敗");
	}
#pragma endregion

#pragma region コンスタントバッファを作っておく
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

void wtgb::Mesh2D::Release(ViewerCached _system)
{
}
