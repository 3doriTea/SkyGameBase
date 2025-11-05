#include "pch\pch.h"
#include "Fbx.h"
#include "ModelResource.h"
#include "WTGBAssert.h"
#include "GameSystem/Direct3D.h"

#include "GameSystem/Debug.h"

wtgb::Fbx::~Fbx()
{
}

void wtgb::Fbx::Draw(Transform& transform)
{
	using namespace DirectX;

	/*ConstantBuffer cb{};
	cb.matWVP = XMMatrixTranspose*/
}

void wtgb::Fbx::Init()
{
	ufbx_load_opts options{};
	ufbx_error error{};

	ufbx_scene* pScene{ ufbx_load_file(FileName().data(), &options, &error)};
	wassert(pScene != nullptr && "Fbxファイル読み込みに失敗");
	if (pScene == nullptr)
	{
		return;
	}

	for (ufbx_node* pNode : pScene->nodes)
	{
		if (pNode->is_root)
		{
			LOGFLN("ルートのノード名:{}", pNode->name.data);
			ufbx_node* pModelNode{ (*pNode->children.begin()) };

			vertexCount_ = pModelNode->mesh->num_vertices;
			polygonCount_ = pModelNode->mesh->num_triangles;
			materialCount_ = pModelNode->materials.count;

			LOGFLN("頂点数:{}", vertexCount_);
			LOGFLN("ポリゴン数:{}", polygonCount_);
			LOGFLN("まてリアル数:{}", materialCount_);

			InitVertex(pModelNode->mesh, pModelNode->mesh->material_parts.begin());
			InitIndex(pModelNode->mesh);
			InitConstant();

			break;
		}
	}

	ufbx_free_scene(pScene);
}

void wtgb::Fbx::Release()
{
	// 明示的に解放

	pVertexBuffer_.Reset();
	pIndexBuffer_.Reset();
	pConstantBuffer_.Reset();
}

void wtgb::Fbx::InitTest(ufbx_mesh* pMesh)
{

}

void wtgb::Fbx::InitVertex(ufbx_mesh* pMesh, ufbx_mesh_part* pPart)
{
	std::vector<Vertex> vertexes{};
	std::vector<uint32_t> triangleIndices{};
	triangleIndices.resize(pMesh->max_face_triangles * 3);

	for (uint32_t faceIndex : pPart->face_indices)
	{
		ufbx_face face{ pMesh->faces[faceIndex] };

		uint32_t numberTriangles
		{
			ufbx_triangulate_face(
				triangleIndices.data(),
				triangleIndices.size(),
				pMesh,
				face)
		};

		for (size_t i = 0; i < numberTriangles * 3; i++)
		{
			uint32_t index{ triangleIndices[i] };

			Vertex vertex{};
			vertex.position =
			{
				static_cast<float>(pMesh->vertex_position[index].x),
				static_cast<float>(pMesh->vertex_position[index].y),
				static_cast<float>(pMesh->vertex_position[index].z),
			};
			vertex.normal =
			{
				static_cast<float>(pMesh->vertex_normal[index].x),
				static_cast<float>(pMesh->vertex_normal[index].y),
				static_cast<float>(pMesh->vertex_normal[index].z),
			};
			vertex.uv =
			{
				static_cast<float>(pMesh->vertex_uv[index].x),
				static_cast<float>(pMesh->vertex_uv[index].y),
			};
			vertexes.push_back(vertex);
		}
	}

	indexCount_ = pPart->num_triangles * 3;
	assert(vertexes.size() == indexCount_ && "頂点数とインデックス数が不一致");

	const size_t STREAM_SIZE{ 1 };
	ufbx_vertex_stream streams[STREAM_SIZE]
	{
		{ vertexes.data(), vertexes.size(), sizeof(Vertex) }
	};
	std::vector<uint32_t> indexes{};
	indexes.resize(indexCount_);

	size_t num_vertexes{ ufbx_generate_indices(streams, STREAM_SIZE, indexes.data(), indexCount_, nullptr, nullptr) };

	vertexes.resize(num_vertexes);

	ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
	HRESULT hResult{};

#pragma region 頂点バッファ作成
	const D3D11_BUFFER_DESC VERTEX_DESC
	{
		// 型の大きさ
		.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertexCount_),
		.Usage = D3D11_USAGE_DEFAULT,                // 変更するか
		.BindFlags = D3D11_BIND_VERTEX_BUFFER,       // なんのバッファか
		.CPUAccessFlags = 0,                         // CPUからのアクセスフラグ
		.MiscFlags = 0,                              // その他のフラグ
		.StructureByteStride = 0,
	};
	const D3D11_SUBRESOURCE_DATA VERTEX_DATA
	{
		.pSysMem = vertexes.data(),
		.SysMemPitch = {},
		.SysMemSlicePitch = {},
	};

	hResult = pDevice->CreateBuffer(&VERTEX_DESC, &VERTEX_DATA, pVertexBuffer_.GetAddressOf());
	wassert(SUCCEEDED(hResult) && "Fbx頂点バッファ作成に失敗");
#pragma endregion

#pragma region インデックスバッファ作成
	const D3D11_BUFFER_DESC INDEX_DESC
	{
		// 型の大きさ
		.ByteWidth = static_cast<UINT>(sizeof(uint32_t) * polygonCount_ * 3),
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
	wassert(SUCCEEDED(hResult) && "Fbxインデックスバッファ作成に失敗");
#pragma endregion
}

void wtgb::Fbx::InitIndex(ufbx_mesh* pMesh)
{
}

void wtgb::Fbx::InitConstant()
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
	wassert(SUCCEEDED(hResult) && "Fbxコンスタントバッファ作成に失敗");

}
