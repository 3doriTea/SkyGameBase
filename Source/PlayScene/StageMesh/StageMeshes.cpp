#include "StageMeshes.h"

StageMeshes::StageMeshes(StagePoints& _points, float& _textureScale) :
	points_{ _points },
	hTextures_{},
	vertexCounts_{},
	indexCounts_{},
	textureScale_{ _textureScale }
{
}

StageMeshes::~StageMeshes()
{
}

void StageMeshes::Init(ViewerCached _system)
{
	GenerateVertices(_system);
	GenerateIndices(_system);
	GenerateConstant(_system);
}

void StageMeshes::Release(ViewerCached _system)
{
}

void StageMeshes::SetPosXValue(const float _xValue, Vertex* _vertex)
{
	_vertex->position.x = _xValue;
	_vertex->uv.x = _xValue;
}

void StageMeshes::GenerateVertices(ViewerCached _system)
{
	using namespace DirectX;

	pVertexBuffers_.clear();

	if (points_.size() < 2)
	{
		wassert(false && "平面頂点数が2以上でないと描画できない");
		return;
	}

	// 面
	for (int i = 0; i < points_.size() - 1; i++)
	{
		PlaneVertices vertices{};  // 頂点ず
		
		Vector2 pos2DCurr{ static_cast<float>(points_[i].x), static_cast<float>(points_[i].y) };
		Vector2 pos2DNext{ static_cast<float>(points_[i + 1].x), static_cast<float>(points_[i + 1].y) };
	
		const float UV_BEGIN_X{ 0.0f };
		const float UV_BEGIN_Y{ pos2DCurr.x / textureScale_ };
		const float UV_END_X{ textureScale_ };
		const float UV_END_Y{ pos2DNext.x / textureScale_ };

		Vector3 toNext{ 0.0f, pos2DNext.y - pos2DCurr.y, pos2DNext.x - pos2DCurr.x };
		Vector3 toForwardNorm{ XMVector3Normalize(toNext) };
		Vector3 toRightNorm{ Vector3::Right() };
		
		// MEMO: 2つの軸が確定しているので法線を求められる
		Vector3 toUpNorm{ XMVector3Cross(toForwardNorm, toRightNorm) };

		vertices[VERTEX_BOTTOM_LEFT] =
		{
			.position = { 0.0f, pos2DCurr.y, pos2DCurr.x },
			.normal = toUpNorm,
			.uv = { UV_BEGIN_X, UV_BEGIN_Y },
		};
		vertices[VERTEX_BOTTOM_RIGHT] =
		{
			.position = { 1.0f, pos2DCurr.y, pos2DCurr.x },
			.normal = toUpNorm,
			.uv = { UV_END_X, UV_BEGIN_Y },
		};
		vertices[VERTEX_TOP_LEFT] =
		{
			.position = { 0.0f, pos2DNext.y, pos2DNext.x },
			.normal = toUpNorm,
			.uv = { UV_BEGIN_X, UV_END_Y },
		};
		vertices[VERTEX_TOP_RIGHT] =
		{
			.position = { 1.0f, pos2DNext.y, pos2DNext.x },
			.normal = toUpNorm,
			.uv = { UV_END_X, UV_END_Y },
		};

		// バッファ作成
		ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

		const D3D11_BUFFER_DESC VERTEX_DESC
		{
			// 型の大きさ
			.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertices.size()),
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

		pVertexBuffers_.push_back({});
		hResult = pDevice->CreateBuffer(
			&VERTEX_DESC,
			&VERTEX_DATA,
			pVertexBuffers_.back().GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュ頂点バッファ作成に失敗");

		LOGFLN("------");
		for (int i = 0; i < vertices.size(); i++)
		{
			LOGFLN(
				"i: {} = position:({}, {}, {}), normal:({}, {}, {}), uv:({}, {})",
				i,
				vertices[i].position.x, vertices[i].position.y, vertices[i].position.z,
				vertices[i].normal.x, vertices[i].normal.y, vertices[i].normal.z,
				vertices[i].uv.x, vertices[i].uv.y);
		}
	}
}

void StageMeshes::GenerateIndices(ViewerCached _system)
{
	pIndexBuffers_.clear();
	indexCounts_.clear();
	for (int i = 0; i < points_.size() - 1; i++)
	{
		static const size_t INDEX_COUNT{ 6 };
		//static const std::array<uint32_t, INDEX_COUNT> INDEX_SET_ARRAY{ 0, 2, 1, 2, 3, 1 };
		static const std::array<uint32_t, INDEX_COUNT> INDEX_SET_ARRAY{ 0, 1, 2, 0, 2, 3 };

		ID3D11Device* pDevice{ _system.Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

		const D3D11_BUFFER_DESC INDEX_DESC
		{
			// 型の大きさ
			.ByteWidth = static_cast<UINT>(sizeof(uint32_t) * INDEX_SET_ARRAY.size()),
			.Usage = D3D11_USAGE_DEFAULT,                // 変更するか
			.BindFlags = D3D11_BIND_INDEX_BUFFER,        // なんのバッファか
			.CPUAccessFlags = 0,                         // CPUからのアクセスフラグ
			.MiscFlags = 0,                              // その他のフラグ
			.StructureByteStride = 0,
		};
		const D3D11_SUBRESOURCE_DATA INDEX_DATA
		{
			.pSysMem = INDEX_SET_ARRAY.data(),
			.SysMemPitch = {},
			.SysMemSlicePitch = {},
		};

		pIndexBuffers_.push_back({});
		indexCounts_.push_back(INDEX_COUNT);
		hResult = pDevice->CreateBuffer(&INDEX_DESC, &INDEX_DATA, pIndexBuffers_.back().GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュのインデックスバッファ作成に失敗");
	}
}

void StageMeshes::GenerateConstant(ViewerCached _system)
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
