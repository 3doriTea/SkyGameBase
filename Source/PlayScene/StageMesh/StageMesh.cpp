#include "pch\pch.h"
#include "StageMesh.h"
#include "WTGBAssert.h"

using namespace wtgb;


StageMesh::StageMesh(StagePoints& _points) :
	points_{ _points },
	hTexture_{ INVALID_HANDLE },
	vertexCount_{},
	indexCount_{}
{
}

StageMesh::~StageMesh()
{
}

void StageMesh::Init(ViewerCached _system)
{
	GenerateVertices(_system);

	GenerateIndices(_system);

	GenerateConstant(_system);
}

void StageMesh::Release(ViewerCached _system)
{
}

void StageMesh::SetPosXValue(const float _xValue, Vertex* _vertex)
{
	_vertex->position.x = _xValue;
	_vertex->uv.x = _xValue;
}

void StageMesh::GenerateVertices(ViewerCached _system)
{
	using namespace DirectX;

	// 頂点ず
	std::vector<Vertex> vertices;

	const float TEXTURE_BEGIN_U{ 0.0f };
	const float TEXTURE_SCALE_U{ 20.0f };

	if (points_.size() < 2)
	{
		wassert(false && "平面頂点数が2以上でないと描画できない");
		return;
	}

	int size = 0;
	for (int i = 0; i < points_.size(); i++)
	{
		Vector2 pos2D{ static_cast<float>(points_[i].x), static_cast<float>(points_[i].y) };
		Vertex v
		{
			.position = { 0.0f, pos2D.y, pos2D.x },
			.normal = { 0.0f, 1.0f, 0.0f },
			.uv = { 0.0f, static_cast<float>(pos2D.x) / TEXTURE_SCALE_U }
		};
		if (i == 0)  // 最初のポイントなら
		{
			Vector2 toPrev2D{ 0.0f, 1.0f };
			Vector2 posNext2D{ static_cast<float>(points_[i + 1].x), static_cast<float>(points_[i + 1].y) };
			Vector2 toNext2D{ posNext2D - pos2D };

			Vector2 normal2D{ DirectX::XMVector3Normalize(toPrev2D + toNext2D) };
			v.normal = { 0.0f, normal2D.y, normal2D.x };

			// 下向きの法線ができてしまったら上向きに変換
			if (v.normal.y <= 0.0f)
			{
				v.normal = v.normal * -1.0f;
			}

			SetPosXValue(0.0f, &v);
			vertices.push_back(v);
			SetPosXValue(1.0f, &v);
			vertices.push_back(v);
		}
		else if (i == points_.size() - 1)  // 最後のポイントなら
		{
			Vector2 posPrev2D{ static_cast<float>(points_[i - 1].x), static_cast<float>(points_[i - 1].y) };
			Vector2 toPrev2D{ posPrev2D - pos2D };
			Vector2 toNext2D{ 0.0f, 1.0f };

			Vector2 normal2D{ XMVector3Normalize(toPrev2D + toNext2D) };
			v.normal = { 0.0f, normal2D.y, normal2D.x };

			// 下向きの法線ができてしまったら上向きに変換
			if (v.normal.y <= 0.0f)
			{
				v.normal = v.normal * -1.0f;
			}

			SetPosXValue(0.0f, &v);
			vertices.push_back(v);
			SetPosXValue(1.0f, &v);
			vertices.push_back(v);
		}
		else  // 最初以外の中間ポイント
		{
			Vector2 posPrev2D{ static_cast<float>(points_[i - 1].x), static_cast<float>(points_[i - 1].y) };
			Vector2 toPrev2D{ posPrev2D - pos2D };
			Vector2 posNext2D{ static_cast<float>(points_[i + 1].x), static_cast<float>(points_[i + 1].y) };
			Vector2 toNext2D{ posNext2D - pos2D };

			Vector3 prevNormal{ XMVector3Normalize(XMVector3Cross(Vector3::Right(), Vector3{ 0.0f, toPrev2D.y, toPrev2D.x })) };
			Vector3 nextNormal{ XMVector3Normalize(XMVector3Cross(Vector3::Right(), Vector3{ 0.0f, toNext2D.y, toNext2D.x })) };

			v.normal = XMVector3Normalize(prevNormal + nextNormal);

			// 下向きの法線ができてしまったら上向きに変換
			if (v.normal.y <= 0.0f)
			{
				v.normal = v.normal * -1.0f;
			}

			SetPosXValue(0.0f, &v);
			v.uv.x = TEXTURE_BEGIN_U;
			vertices.push_back(v);
			SetPosXValue(1.0f, &v);
			v.uv.x = TEXTURE_SCALE_U;
			vertices.push_back(v);
		}
		size++;
	}

	vertexCount_ = static_cast<uint32_t>(vertices.size());

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
		.pSysMem = vertices.data(),
		.SysMemPitch = {},
		.SysMemSlicePitch = {},
	};

	hResult = pDevice->CreateBuffer(&VERTEX_DESC, &VERTEX_DATA, pVertexBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ステージメッシュ頂点バッファ作成に失敗");
}

void StageMesh::GenerateIndices(ViewerCached _system)
{
	// インデクスたち
	std::vector<uint32_t> indexes{};

	static const uint32_t INDEX_SET_ARRAY[]{ 0, 2, 1, 2, 3, 1 };
	static const size_t INDEX_SET_ARRAY_SIZE{ sizeof(INDEX_SET_ARRAY) / sizeof(int) };

	size_t polyCount{ (points_.size() - 1) * 2 };

	int indexCount{ 0 };
	for (int p = 0; p < polyCount; p++)
	{
		for (int i = 0; i < 3; i++)
		{
			indexes.push_back(
				INDEX_SET_ARRAY[(p * 3 + i) % INDEX_SET_ARRAY_SIZE]
				+ 2 * (indexCount / INDEX_SET_ARRAY_SIZE));
			indexCount++;
		}
	}
	indexCount_ = static_cast<uint32_t>(indexes.size());


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
		.pSysMem = indexes.data(),
		.SysMemPitch = {},
		.SysMemSlicePitch = {},
	};

	hResult = pDevice->CreateBuffer(&INDEX_DESC, &INDEX_DATA, pIndexBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "ステージメッシュのインデックスバッファ作成に失敗");
}

void StageMesh::GenerateConstant(ViewerCached _system)
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
