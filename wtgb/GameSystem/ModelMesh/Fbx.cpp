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
	fs::path current{ fs::current_path() };
	modelFile_ = current / FileName();

	FbxManager* pFbxManager{ FbxManager::Create() };
	FbxImporter* pFbxImporter{ FbxImporter::Create(pFbxManager, "importer") };
	pFbxImporter->Initialize(modelFile_.string().c_str(), -1, pFbxManager->GetIOSettings());

	FbxScene* pFbxScene{ FbxScene::Create(pFbxManager, "fbx-scene")};
	pFbxImporter->Import(pFbxScene);

	FbxNode* pRootNode{ pFbxScene->GetRootNode() };
	FbxNode* pNode{ pRootNode->GetChild(0) };
	FbxMesh* pMesh{ pNode->GetMesh() };

	vertexCount_ = pMesh->GetControlPointsCount();  // 頂点数
	polygonCount_ = pMesh->GetPolygonCount();       // ポリゴン数
	materialCount_ = pNode->GetMaterialCount();     // マテリアル数

	InitVertex(pMesh);
	InitIndex(pMesh);
	InitConstant();
	InitMaterial(pNode);

	pFbxScene->Destroy();
	pFbxImporter->Destroy();
	pFbxManager->Destroy();
}

void wtgb::Fbx::Release()
{
	// 明示的に解放

	pVertexBuffer_.Reset();
	for (auto& pIndexBuffer : pIndexBuffers_)
	{
		pIndexBuffer.Reset();
	}
	pConstantBuffer_.Reset();
}

void wtgb::Fbx::InitVertex(FbxMesh* _pMesh)
{
	enum { X, Y, Z };
	enum { U, V };

	std::vector<Vertex> vertexes{};
	vertexes.resize(vertexCount_);

	// 頂点のUV
	FbxLayerElementUV* pUV = _pMesh->GetLayer(0)->GetUVs();
	FbxLayerElement::EMappingMode mappingMode{ pUV->GetMappingMode() };
	FbxLayerElement::EReferenceMode referenceMode{ pUV->GetReferenceMode() };

	for (int p = 0; p < polygonCount_; p++)
	{
		for (int v = 0; v < 3; v++)
		{
			int index{ _pMesh->GetPolygonVertex(p, v) };

			FbxVector4 position{ _pMesh->GetControlPointAt(index) };
			vertexes[index].position =
			{
				static_cast<float>(position[X]),
				static_cast<float>(position[Y]),
				static_cast<float>(position[Z])
			};

			int uvIndex{ 0 };
			FbxVector2 uv{ pUV->GetDirectArray().GetAt(uvIndex) };

			// mapping mode で分岐
			switch (mappingMode)
			{
				break;
			case fbxsdk::FbxLayerElement::eByControlPoint:
				uvIndex = index;
				break;
			case fbxsdk::FbxLayerElement::eByPolygonVertex:
				uvIndex = _pMesh->GetTextureUVIndex(p, v, FbxLayerElement::eTextureDiffuse);
				break;
			case fbxsdk::FbxLayerElement::eNone:
			case fbxsdk::FbxLayerElement::eByPolygon:
			case fbxsdk::FbxLayerElement::eByEdge:
			case fbxsdk::FbxLayerElement::eAllSame:
			default:
				uv = { 0, 0 };
				break;
			}

			// reference mode で分岐
			switch (referenceMode)
			{
			case fbxsdk::FbxLayerElement::eDirect:
				uv = pUV->GetDirectArray().GetAt(uvIndex);
				break;
			case fbxsdk::FbxLayerElement::eIndexToDirect:
				uv = pUV->GetDirectArray().GetAt(
					pUV->GetIndexArray().GetAt(uvIndex));
				break;
			case fbxsdk::FbxLayerElement::eIndex:
			default:
				break;
			}

			// UVを取得
			// NOTE: UVの縦方向の基準が逆になるため逆にする
			vertexes[index].uv =
			{
				static_cast<float>(uv.mData[U]),
				1.0f - static_cast<float>(uv.mData[U])
			};

			// 法線を取得
			FbxVector4 normal{};
			_pMesh->GetPolygonVertexNormal(p, v, normal);
			vertexes[index].normal =
			{
				static_cast<float>(normal[X]),
				static_cast<float>(normal[Y]),
				static_cast<float>(normal[Z])
			};
		}
	}

#pragma region 頂点バッファ作成
	ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
	HRESULT hResult{};

	const D3D11_BUFFER_DESC VERTEX_DESC
	{
		// 型の大きさ
		.ByteWidth = static_cast<UINT>(sizeof(Vertex) * vertexCount_),
		.Usage = D3D11_USAGE_DEFAULT,                // 変更するか
		//.Usage = D3D11_USAGE_STAGING,                // 変更するか
		.BindFlags = D3D11_BIND_VERTEX_BUFFER,       // なんのバッファか
		.CPUAccessFlags = 0,                         // CPUからのアクセスフラグ
		//.CPUAccessFlags = D3D11_CPU_ACCESS_READ,    // TODO: テスト用                     // CPUからのアクセスフラグ
		.MiscFlags = 0,                              // その他のフラグ
		.StructureByteStride = sizeof(Vertex),
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
}

void wtgb::Fbx::InitIndex(FbxMesh* _pMesh)
{
	// マテリアルの数だけ作る
	pIndexBuffers_.resize(materialCount_);  // インデックスバッファ
	indexCounts_.resize(materialCount_);    // インデックス数

	std::vector<int> indexes{};
	indexes.resize(polygonCount_ * 3);

	// 各マテリアルごとに
	for (int i = 0; i < materialCount_; i++)
	{
		int count{ 0 };

		for (int p = 0; p < polygonCount_; p++)
		{
			FbxLayerElementMaterial* pMaterial{ _pMesh->GetLayer(0)->GetMaterials() };
			int materialId{ pMaterial->GetIndexArray().GetAt(p) };

			if (materialId == i)
			{
				for (int vertex = 0; vertex < 3; vertex++)
				{
					indexes[count] = _pMesh->GetPolygonVertex(p, vertex);
					count++;
				}
			}
		}

		indexCounts_[i] = count;

#pragma region 各マテリアル - インデックスバッファ作成
		ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
		HRESULT hResult{};

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

		hResult = pDevice->CreateBuffer(&INDEX_DESC, &INDEX_DATA, pIndexBuffers_[i].GetAddressOf());
		wassert(SUCCEEDED(hResult) && "Fbxインデックスバッファ作成に失敗");
#pragma endregion
	}
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

void wtgb::Fbx::InitMaterial(FbxNode* _pNode)
{
	enum { R, G, B };

	materials_.resize(materialCount_);

	for (int i = 0; i < materialCount_; i++)
	{
		FbxSurfaceMaterial* pMaterial{ _pNode->GetMaterial(i) };
		if (pMaterial == nullptr)
		{
			wassert(false && "マテリアルの取得に失敗");
			continue;
		}

		fbxsdk::FbxProperty fbxProperty{ pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse) };
		if (!fbxProperty.IsValid())
		{
			wassert(false && "無効なプロパティ値");
			continue;
		}

#pragma region テクスチャ関係
		int fileTextureCount{ fbxProperty.GetSrcObjectCount<FbxFileTexture>() };

		materials_[i].textureFile = "";
		
		if (fileTextureCount > 0)  // テクスチャが貼ってあるなら
		{
			FbxFileTexture* pTextureInfo{ fbxProperty.GetSrcObject<FbxFileTexture>(0) };
			fs::path textureFile{ modelFile_.parent_path() / pTextureInfo->GetRelativeFileName() };


			// NOTE: シンボリックリンクやディレクトリを除外するためにis_regular_fileを使うようにする
			//  BAD: fs::exists(materials_[i].textureFile)
			// GOOD: fs::is_regular_file(materials_[i].textureFile)
			if (fs::is_regular_file(textureFile))
			{
				materials_[i].textureFile = textureFile;
			}
			else
			{
				wassert(false && "テクスチャファイルが存在しない");
			}
			
			materials_[i].diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
		}
		else  // テクスチャがないなら
		{
			if (pMaterial->GetClassId().Is(FbxSurfaceLambert::ClassId) == false)
			{
				wassert(false && "ランバートシェーダ以外対応していません");
				return;
			}

			pMaterial->FindProperty(FbxSurfaceLambert::sDiffuse);

			FbxDouble3 color{ reinterpret_cast<FbxSurfaceLambert*>(pMaterial)->Diffuse.Get() };
			materials_[i].diffuse =
			{
				static_cast<float>(color[R]),
				static_cast<float>(color[G]),
				static_cast<float>(color[B]),
				1.0f  // アルファ値は 1.0f
			};
		}

#pragma endregion
	}
}
