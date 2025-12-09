#include "pch\pch.h"
#include "CPMeshRenderer.h"
#include "GameSystem/Debug.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/Model.h"
#include "GameSystem/Direct3D.h"
#include "GameSystem/ModelMesh/Fbx.h"
#include "GameSystem/Camera.h"
#include "GameSystem/ResourceSystem.h"
#include "GameSystem/CPTransform.h"
#include "WTGBAssert.h"
#include "ModelMesh/IMeshSimple2D.h"
#define WTGB_CPMR_USE_VERTEX_LOG 1

wtgb::CPMeshRenderer::CPMeshRenderer()
{
}
wtgb::CPMeshRenderer::~CPMeshRenderer()
{
}

void wtgb::CPMeshRenderer::Render(
	IMeshSimple* _pMeshSimple,
	Transform* _pTransform,
	const ShaderHandle _hShader,
	const Color& _diffuseColor)
{
	using namespace DirectX;

	Camera& camera{ System().Get<Camera>() };
	ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
	Direct3D& d3d{ System().Get<Direct3D>() };
	ID3D11DeviceContext* pContext{ System().Get<Direct3D>().Resource().Context() };


	IMeshSimple* pMesh{ _pMeshSimple };
	wassert(pMesh && "メッシュがない！");
	if (pMesh == nullptr)
	{
		return;
	}

	Transform* pTransform{ _pTransform };
	wassert(pTransform && "座標系がない！");
	if (pTransform == nullptr)
	{
		return;
	}

	IMeshSimple::ConstantBuffer constantBuffer{};
	constantBuffer.matrixWVP = XMMatrixTranspose(pTransform->GetWorldMatrix() * camera.GetViewMatrix() * camera.GetProjectionMatrix());
	constantBuffer.matrixRotateWorld = XMMatrixTranspose(pTransform->GetNormalMatrix());
	constantBuffer.matrixUV = XMMatrixIdentity();
	// TODO: この辺は統一するためにライトオブジェクトを検出して同期させるシステムを作る light system
	constantBuffer.lightDirection = { -0.5f, -0.5f, -0.5f, 0.0f };
	constantBuffer.lightColor = 0xffffff;
	constantBuffer.ambientValue = 0.3f;
	constantBuffer.diffuseColor = _diffuseColor;

	constantBuffer.hasTexture = FALSE;

	// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
	d3d.SetShader(_hShader);

	UINT stride{ static_cast<UINT>(pMesh->GetVertexSize()) };
	UINT offset{ 0 };
	// 頂点バッファをセット
	pContext->IASetVertexBuffers(0, 1, pMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);

	// インデックスバッファをセット
	stride = sizeof(uint32_t);
	offset = 0;
	pContext->IASetIndexBuffer(pMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	// コンスタントバッファをセット
	pContext->VSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
	pContext->PSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用


	D3D11_MAPPED_SUBRESOURCE data{};

	pContext->Map(pMesh->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(
		data.pData,
		data.RowPitch,
		reinterpret_cast<void*>(&constantBuffer),
		sizeof(IMeshSimple::ConstantBuffer));
	pContext->Unmap(pMesh->GetConstantBuffer().Get(), 0);

	pContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);
}

void wtgb::CPMeshRenderer::Render2D(
	IMeshSimple2D* _pMeshSimple,
	const Matrix4x4& _matrixProjection,
	const Matrix4x4& _matrixUV,
	const ShaderHandle _hShader,
	const Color& _color,
	const TextureHandle _hTexture)
{
	using namespace DirectX;

	Camera& camera{ System().Get<Camera>() };
	ResourceSystem& resource{ System().Get<ResourceSystem>() };
	ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
	Direct3D& d3d{ System().Get<Direct3D>() };
	ID3D11DeviceContext* pContext{ System().Get<Direct3D>().Resource().Context() };


	IMeshSimple2D* pMesh{ _pMeshSimple };
	wassert(pMesh && "メッシュがない！");
	if (pMesh == nullptr)
	{
		return;
	}

	IMeshSimple2D::ConstantBuffer constantBuffer{};

	constantBuffer.color = _color;
	constantBuffer.matrixProj = _matrixProjection;
	constantBuffer.matrixUV = XMMatrixTranspose(_matrixUV);
	
	// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
	d3d.SetShader(_hShader);

	UINT stride{ static_cast<UINT>(pMesh->GetVertexSize()) };
	UINT offset{ 0 };
	// 頂点バッファをセット
	pContext->IASetVertexBuffers(0, 1, pMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);

	// インデックスバッファをセット
	stride = sizeof(uint32_t);
	offset = 0;
	pContext->IASetIndexBuffer(pMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

	// コンスタントバッファをセット
	pContext->VSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
	pContext->PSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用

	if (_hTexture != INVALID_HANDLE)
	{
		Texture* pTexture{ resource.GetTexture(_hTexture) };
	
		wassert(pTexture && "テクスチャの読み込みに失敗");
		
		// テクスチャが指定されているなら
		if (pTexture)
		{
			pContext->PSSetSamplers(0, 1, pTexture->GetSamplerState().GetAddressOf());

			pContext->PSSetShaderResources(0, 1, pTexture->GetShaderResourceView().GetAddressOf());
		}
	}

	D3D11_MAPPED_SUBRESOURCE data{};

	pContext->Map(pMesh->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
	memcpy_s(
		data.pData,
		data.RowPitch,
		reinterpret_cast<void*>(&constantBuffer),
		sizeof(IMeshSimple2D::ConstantBuffer));
	pContext->Unmap(pMesh->GetConstantBuffer().Get(), 0);

	pContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);

#if 0
	{
		size_t vertexCount = pMesh->GetVertexCount();
		std::vector<IMeshSimple2D::Vertex> vertexes{};
		vertexes.resize(vertexCount);

		// 1. 元バッファの情報取得
		D3D11_BUFFER_DESC desc{};
		pMesh->GetVertexBuffer()->GetDesc(&desc);

		// 2. 読み取り用ステージングバッファの設定
		D3D11_BUFFER_DESC stagingDesc = desc;
		stagingDesc.Usage = D3D11_USAGE_STAGING;
		stagingDesc.BindFlags = 0;
		stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		stagingDesc.MiscFlags = 0;

		// 3. ステージングバッファを作成
		ComPtr<ID3D11Buffer> pStagingBuffer{};
		HRESULT hr = pDevice->CreateBuffer(&stagingDesc, nullptr, &pStagingBuffer);
		if (FAILED(hr))
		{
			wassert(false && "ステージングバッファの作成に失敗");
			return;
		}

		// 4. GPUバッファからステージングバッファにコピー
		pContext->CopyResource(pStagingBuffer.Get(), pMesh->GetVertexBuffer().Get());

		// 5. ステージングバッファをマップしてCPUで読み込み
		D3D11_MAPPED_SUBRESOURCE mapped{};
		hr = pContext->Map(pStagingBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
		if (SUCCEEDED(hr))
		{
			// バッファの内容をコピー
			memcpy(vertexes.data(), mapped.pData, sizeof(IMeshSimple2D::Vertex) * vertexCount);
			pContext->Unmap(pStagingBuffer.Get(), 0);
		}

		LOGFLN("----------------------------");
		for (auto& vertex : vertexes)
		{
			LOGFLN("POS:({},{},{})", vertex.position.x, vertex.position.y, vertex.position.z);
			LOGFLN("UV:({},{})", vertex.uv.x, vertex.uv.y);
		}

		pStagingBuffer.Reset();
	}
	{
		size_t indexCount = pMesh->GetIndexCount();
		std::vector<uint32_t> indexes{};
		indexes.resize(indexCount);

		// 1. 元バッファの情報取得
		D3D11_BUFFER_DESC desc{};
		pMesh->GetIndexBuffer()->GetDesc(&desc);

		// 2. 読み取り用ステージングバッファの設定
		D3D11_BUFFER_DESC stagingDesc = desc;
		stagingDesc.Usage = D3D11_USAGE_STAGING;
		stagingDesc.BindFlags = 0;
		stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		stagingDesc.MiscFlags = 0;

		// 3. ステージングバッファを作成
		ComPtr<ID3D11Buffer> pStagingBuffer{};
		HRESULT hr = pDevice->CreateBuffer(&stagingDesc, nullptr, &pStagingBuffer);
		if (FAILED(hr))
		{
			wassert(false && "ステージングバッファの作成に失敗");
			return;
		}

		// 4. GPUバッファからステージングバッファにコピー
		pContext->CopyResource(pStagingBuffer.Get(), pMesh->GetIndexBuffer().Get());

		// 5. ステージングバッファをマップしてCPUで読み込み
		D3D11_MAPPED_SUBRESOURCE mapped{};
		hr = pContext->Map(pStagingBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
		if (SUCCEEDED(hr))
		{
			// バッファの内容をコピー
			memcpy(indexes.data(), mapped.pData, sizeof(uint32_t) * indexCount);
			pContext->Unmap(pStagingBuffer.Get(), 0);
		}

		LOGFLN("----------------------------");
		for (int i = 0; i < indexes.size(); i++)
		{
			LOGFLN("index[{}]:{}", i, indexes[i]);
		}

		pStagingBuffer.Reset();
	}
#endif
}

void wtgb::CPMeshRenderer::Init()
{
}

void wtgb::CPMeshRenderer::Update()
{
	// TODO: それぞれのレンダリング処理を分ける

	using namespace DirectX;

	Camera& camera{ System().Get<Camera>() };
	ID3D11Device* pDevice{ System().Get<Direct3D>().Resource().Device() };
	CPGameObject& cpGameObject{ System().Get<CPGameObject>() };
	CPTransform& cpTransform{ System().Get<CPTransform>() };
	CPModelMesh& cpModelMesh{ System().Get<CPModelMesh>() };
	Model& model{ System().Get<Model>() };
	Direct3D& d3d{ System().Get<Direct3D>() };
	ResourceSystem& resource{ System().Get<ResourceSystem>() };
	ID3D11DeviceContext* pContext{ System().Get<Direct3D>().Resource().Context() };
	
	ForEach([&camera, &pDevice, &cpGameObject, &cpTransform, &cpModelMesh, &model, &d3d, &resource, pContext]
		(MeshRenderer& meshRenderer, const size_t _index)
		{
			EntityId entityId{ cpGameObject.GetEntityId(_index) };

			ModelMesh* pModelMesh{ cpModelMesh.Get(entityId) };
			if (pModelMesh == nullptr)  // 無効なメッシュコンポーネントを取得してしまったら回帰
			{
				return;
			}

			Transform* pTransform{ cpTransform.Get(entityId) };
			if (pTransform == nullptr)
			{
				wassert(false && "Transformの取得に失敗");
				return;
			}

			if (pModelMesh->GetType() == ModelMesh::Type::Fbx)
			{
				ModelHandle hModel{ pModelMesh->hModel_ };
				ModelResource* pModel{ model.GetModel(hModel) };
				Fbx* pFbxModel{ dynamic_cast<Fbx*>(pModel) };
				if (pFbxModel == nullptr)
				{
					LOGFLN("Warn:Fbx以外のモデルが読み込まれた！");
					return;
				}

				Fbx::ConstantBuffer constantBuffer{};
				constantBuffer.matrixWVP = XMMatrixTranspose(pTransform->GetWorldMatrix() * camera.GetViewMatrix() * camera.GetProjectionMatrix());
				constantBuffer.matrixRotateWorld = XMMatrixTranspose(pTransform->GetNormalMatrix());
				constantBuffer.matrixUV = XMMatrixIdentity();
				constantBuffer.lightDirection = { -0.5f, -0.5f, -0.5f, 0.0f };
				constantBuffer.lightColor = 0xffffff;
				constantBuffer.ambientValue = 0.3f;

				// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
				d3d.SetShader(meshRenderer.hShader_);

				UINT stride{ sizeof(Fbx::Vertex) };
				UINT offset{ 0 };
				// 頂点バッファをセット
				pContext->IASetVertexBuffers(0, 1, pFbxModel->GetVertexBuffer().GetAddressOf(), &stride, &offset);

				// 各マテリアル分
				for (int i = 0; i < pFbxModel->GetMaterialCount(); i++)
				{
					constantBuffer.hasTexture = pFbxModel->GetMaterialAt(i).hTexture_ != INVALID_HANDLE;

					//constantBuffer.diffuse = pFbxModel->GetMaterialAt(i).diffuse;
					//bool useTexture{ pFbxModel->GetMaterialAt(i).textureFile != "" };
					//bool useTexture{ pFbxModel->GetMaterialAt(i).hTexture_ != INVALID_HANDLE };
					TextureHandle hTexture{ pFbxModel->GetMaterialAt(i).hTexture_ };

					hTexture = meshRenderer.hTexture_;


					// インデックスバッファをセット
					stride = sizeof(int);
					offset = 0;
					pContext->IASetIndexBuffer(pFbxModel->GetIndexBufferAt(i).Get(), DXGI_FORMAT_R32_UINT, 0);

					// コンスタントバッファをセット
					pContext->VSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
					pContext->PSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用

					if (constantBuffer.hasTexture)
					{
						Texture* pTexture{ resource.GetTexture(hTexture) };
						wassert(pTexture != nullptr);
						if (pTexture)
						{
							//ID3D11SamplerState* pSampler{ pTexture->GetSamplerState() };
							pContext->PSSetSamplers(0, 1, pTexture->GetSamplerState().GetAddressOf());

							//ID3D11ShaderResourceView* pSRV{ };
							pContext->PSSetShaderResources(0, 1, pTexture->GetShaderResourceView().GetAddressOf());
						}
					}
					else
					{
						constantBuffer.diffuseColor = pFbxModel->GetMaterialAt(i).diffuse;
					}
					//constantBuffer.materialFLag = useTexture;

					D3D11_MAPPED_SUBRESOURCE data{};

					pContext->Map(pFbxModel->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
					memcpy_s(
						data.pData,
						data.RowPitch,
						reinterpret_cast<void*>(&constantBuffer),
						sizeof(Fbx::ConstantBuffer));
					pContext->Unmap(pFbxModel->GetConstantBuffer().Get(), 0);

					pContext->DrawIndexed(static_cast<UINT>(pFbxModel->GetIndexCountAt(i)), 0, 0);
				}
			}
			else if (pModelMesh->GetType() == ModelMesh::Type::SimpleMesh)
			{
				IMeshSimple* pMesh{ pModelMesh->pOriginalMesh_ };
				wassert(pMesh && "メッシュがない！");
				if (pMesh == nullptr)
				{
					return;
				}

				IMeshSimple::ConstantBuffer constantBuffer{};
				constantBuffer.matrixWVP = XMMatrixTranspose(pTransform->GetWorldMatrix() * camera.GetViewMatrix() * camera.GetProjectionMatrix());
				constantBuffer.matrixRotateWorld = XMMatrixTranspose(pTransform->GetNormalMatrix());
				constantBuffer.matrixUV = XMMatrixIdentity();
				// TODO: この辺は統一するためにライトオブジェクトを検出して同期させるシステムを作る light system
				constantBuffer.lightDirection = { -0.5f, -0.5f, -0.5f, 0.0f };
				constantBuffer.lightColor = 0xffffff;
				constantBuffer.ambientValue = 0.3f;
				constantBuffer.diffuseColor = { 0.0f, 0.7f, 0.0f, 1.0f };
				
				constantBuffer.hasTexture = FALSE;

				// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
				d3d.SetShader(meshRenderer.hShader_);

				UINT stride{ static_cast<UINT>(pMesh->GetVertexSize()) };
				UINT offset{ 0 };
				// 頂点バッファをセット
				pContext->IASetVertexBuffers(0, 1, pMesh->GetVertexBuffer().GetAddressOf(), &stride, &offset);

				// インデックスバッファをセット
				stride = sizeof(uint32_t);
				offset = 0;
				pContext->IASetIndexBuffer(pMesh->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

				// コンスタントバッファをセット
				pContext->VSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
				pContext->PSSetConstantBuffers(0, 1, pMesh->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用

				// テクスチャが指定されているなら使う
				if (meshRenderer.hTexture_ != INVALID_HANDLE)
				{
					Texture* pTexture{ resource.GetTexture(meshRenderer.hTexture_) };
					wassert(pTexture != nullptr);
					if (pTexture)
					{
						constantBuffer.hasTexture = TRUE;  // テクスチャあるよ

						pContext->PSSetSamplers(0, 1, pTexture->GetSamplerState().GetAddressOf());

						pContext->PSSetShaderResources(0, 1, pTexture->GetShaderResourceView().GetAddressOf());
					}
				}

				D3D11_MAPPED_SUBRESOURCE data{};

				pContext->Map(pMesh->GetConstantBuffer().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &data);
				memcpy_s(
					data.pData,
					data.RowPitch,
					reinterpret_cast<void*>(&constantBuffer),
					sizeof(IMeshSimple::ConstantBuffer));
				pContext->Unmap(pMesh->GetConstantBuffer().Get(), 0);

				pContext->DrawIndexed(pMesh->GetIndexCount(), 0, 0);


#if WTGB_CPMR_USE_VERTEX_LOG
				{
					size_t vertexCount = pMesh->GetVertexCount();
					std::vector<IMeshSimple::Vertex> vertexes{};
					vertexes.resize(vertexCount);

					// 1. 元バッファの情報取得
					D3D11_BUFFER_DESC desc{};
					pMesh->GetVertexBuffer()->GetDesc(&desc);

					// 2. 読み取り用ステージングバッファの設定
					D3D11_BUFFER_DESC stagingDesc = desc;
					stagingDesc.Usage = D3D11_USAGE_STAGING;
					stagingDesc.BindFlags = 0;
					stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					stagingDesc.MiscFlags = 0;

					// 3. ステージングバッファを作成
					ComPtr<ID3D11Buffer> pStagingBuffer{};
					HRESULT hr = pDevice->CreateBuffer(&stagingDesc, nullptr, &pStagingBuffer);
					if (FAILED(hr))
					{
						wassert(false && "ステージングバッファの作成に失敗");
						return;
					}

					// 4. GPUバッファからステージングバッファにコピー
					pContext->CopyResource(pStagingBuffer.Get(), pMesh->GetVertexBuffer().Get());

					// 5. ステージングバッファをマップしてCPUで読み込み
					D3D11_MAPPED_SUBRESOURCE mapped{};
					hr = pContext->Map(pStagingBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
					if (SUCCEEDED(hr))
					{
						// バッファの内容をコピー
						memcpy(vertexes.data(), mapped.pData, sizeof(IMeshSimple::Vertex) * vertexCount);
						pContext->Unmap(pStagingBuffer.Get(), 0);
					}

					/*LOGFLN("----------------------------");
					for (auto& vertex : vertexes)
					{
						LOGFLN("POS:({},{},{})", vertex.position.x, vertex.position.y, vertex.position.z);
						LOGFLN("NORM:({},{},{})", vertex.normal.x, vertex.normal.y, vertex.normal.z);
						LOGFLN("UV:({},{})", vertex.uv.x, vertex.uv.y);
					}*/

					pStagingBuffer.Reset();
				}
#endif

#if 0 //WTGB_CPMR_USE_INDEX_LOG
				{
					size_t indexCount = pMesh->GetIndexCount();
					std::vector<uint32_t> indexes{};
					indexes.resize(indexCount);

					// 1. 元バッファの情報取得
					D3D11_BUFFER_DESC desc{};
					pMesh->GetIndexBuffer()->GetDesc(&desc);

					// 2. 読み取り用ステージングバッファの設定
					D3D11_BUFFER_DESC stagingDesc = desc;
					stagingDesc.Usage = D3D11_USAGE_STAGING;
					stagingDesc.BindFlags = 0;
					stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
					stagingDesc.MiscFlags = 0;

					// 3. ステージングバッファを作成
					ComPtr<ID3D11Buffer> pStagingBuffer{};
					HRESULT hr = pDevice->CreateBuffer(&stagingDesc, nullptr, &pStagingBuffer);
					if (FAILED(hr))
					{
						wassert(false && "ステージングバッファの作成に失敗");
						return;
					}

					// 4. GPUバッファからステージングバッファにコピー
					pContext->CopyResource(pStagingBuffer.Get(), pMesh->GetIndexBuffer().Get());

					// 5. ステージングバッファをマップしてCPUで読み込み
					D3D11_MAPPED_SUBRESOURCE mapped{};
					hr = pContext->Map(pStagingBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
					if (SUCCEEDED(hr))
					{
						// バッファの内容をコピー
						memcpy(indexes.data(), mapped.pData, sizeof(uint32_t) * indexCount);
						pContext->Unmap(pStagingBuffer.Get(), 0);
					}

					/*LOGFLN("----------------------------");
					for (int i = 0; i < indexes.size(); i++)
					{
						LOGFLN("index[{}]:{}", i, indexes[i]);
					}*/

					pStagingBuffer.Reset();
				}
#endif

			}
		});
}
