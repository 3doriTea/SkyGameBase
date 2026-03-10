#include "pch\pch.h"
#include "WTGBAssert.h"
#include "TestBillBoard.h"

#pragma region BillBoard
TestBillBoard::BillBoard::BillBoard(ViewerCached _system) :
	system_{ _system }
{
}

TestBillBoard::BillBoard::~BillBoard()
{
}

void TestBillBoard::BillBoard::Init(ViewerCached _system)
{
	using namespace DirectX;

	// 頂点ず
	std::vector<Vertex> vertices;

	// 頂点を求める
	{
		vertices =
		{
			// { { POSITION }, { NORMAL }, { UV } }
			{ { -30.0f,  30.0f, 20.0f, 0.0f }, { 0, 0, -1, 0 }, { 0.0f, 0.0f, 0, 0 } },  // 四角形の頂点（左上）
			{ {  30.0f,  30.0f, 20.0f, 0.0f }, { 0, 0, -1, 0 }, { 1.0f, 0.0f, 0, 0 } },  // 四角形の頂点（右上）
			{ {  30.0f, -30.0f, 20.0f, 0.0f }, { 0, 0, -1, 0 }, { 1.0f, 1.0f, 0, 0 } },  // 四角形の頂点（右下）
			{ { -30.0f, -30.0f, 20.0f, 0.0f }, { 0, 0, -1, 0 }, { 0.0f, 1.0f, 0, 0 } },  // 四角形の頂点（左下）
		};

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

	// インデクスたち
	std::vector<uint32_t> indexes{};

	// インデックスを求める
	{
		static const uint32_t INDEX_SET_ARRAY[]{ 0, 2, 3, 0, 1, 2 };
		static const size_t INDEX_SET_ARRAY_SIZE{ sizeof(INDEX_SET_ARRAY) / sizeof(int) };

		size_t polyCount{ 2 };

		for (int poly = 0; poly < polyCount; poly++)
		{
			for (int index = 0; index < 3; index++)
			{
				indexes.push_back(INDEX_SET_ARRAY[(poly * 3 + index) % INDEX_SET_ARRAY_SIZE]);
			}
		}
		indexCount_ = static_cast<uint32_t>(indexes.size());


		ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
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

	for (int i = 0; i < indexes.size(); i++)
	{
		LOGFLN("{}, {}", i, indexes[i]);
	}

	// コンスタントバッファを作っておく
	{
		const D3D11_BUFFER_DESC CONSTANT_DESC
		{
			// 型の大きさ
			.ByteWidth = static_cast<UINT>(sizeof(ConstantBuffer)),
			.Usage = D3D11_USAGE_DYNAMIC,                // 変更するか
			.BindFlags = D3D11_BIND_CONSTANT_BUFFER,     // なんのバッファか
			.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,    // CPUからのアクセスフラグ
			.MiscFlags = 0,                              // その他のフラグ
			.StructureByteStride = 0,
		};

		ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

		hResult = pDevice->CreateBuffer(&CONSTANT_DESC, nullptr, pConstantBuffer_.GetAddressOf());
		wassert(SUCCEEDED(hResult) && "ステージメッシュコンスタントバッファ作成に失敗");
	}
}

void TestBillBoard::BillBoard::Release(ViewerCached _system)
{
}
#pragma endregion

TestBillBoard::TestBillBoard() : GameObject
	{
		[this](GameObjectBuilder& _builder)
		{
			_builder
				.AddComponent<GameObjectProperty>()
					.BeginSetter()
						.name("BillBoard")
					.EndSetter()
				.AddComponent<wtgb::Transform>()
					.BeginSetter()
					.EndSetter()
				.AddComponent<ModelMesh>()
					.BeginSetter()
						//.pOriginalMesh(&this->billBoard_)
						.fileName("Models/Saka/Saka.fbx")
					.EndSetter()
				.AddComponent<MeshRenderer>()
				.BeginSetter()
					.shader("Shader/BillBoard.hlsl")
				.EndSetter()
			.Build();
		}
	},
	billBoard_{ System() }
{
}

TestBillBoard::~TestBillBoard()
{
}

void TestBillBoard::Init()
{
	billBoard_.CallInit(System());
}

void TestBillBoard::Update()
{
}

void TestBillBoard::Release()
{
	billBoard_.CallRelease(System());
}
