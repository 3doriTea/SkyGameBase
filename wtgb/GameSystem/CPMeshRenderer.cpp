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
#define WTGB_CPMR_USE_VERTEX_LOG 0

wtgb::CPMeshRenderer::CPMeshRenderer()
{
}

wtgb::CPMeshRenderer::~CPMeshRenderer()
{
}

void wtgb::CPMeshRenderer::Init()
{
}

void wtgb::CPMeshRenderer::Update()
{
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
			if (entityId.index == 2)
			{
				EntityId entityId{ cpGameObject.GetEntityId(_index) };
			}
			ModelMesh* pModelMesh{ cpModelMesh.Get(entityId) };
			if (pModelMesh == nullptr)  // 無効なメッシュコンポーネントを取得してしまったら回帰
			{
				return;
			}
			ModelHandle hModel{ pModelMesh->hModel_ };
			Transform* pTransform{ cpTransform.Get(entityId) };

			if (pTransform == nullptr)
			{
				wassert(false && "Transformの取得に失敗");
				return;
			}

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

			// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
			d3d.SetShader(meshRenderer.hShader_);

			UINT stride{ sizeof(Fbx::Vertex) };
			UINT offset{ 0 };
			// 頂点バッファをセット
			pContext->IASetVertexBuffers(0, 1, pFbxModel->GetVertexBuffer().GetAddressOf(), &stride, &offset);

			// 各マテリアル分
			for (int i = 0; i < pFbxModel->GetMaterialCount(); i++)
			{
				constantBuffer.diffuseColor = pFbxModel->GetMaterialAt(i).diffuse;

				//constantBuffer.diffuse = pFbxModel->GetMaterialAt(i).diffuse;
				//bool useTexture{ pFbxModel->GetMaterialAt(i).textureFile != "" };
				//bool useTexture{ pFbxModel->GetMaterialAt(i).hTexture_ != INVALID_HANDLE };
				TextureHandle hTexture{ pFbxModel->GetMaterialAt(i).hTexture_ };


				// インデックスバッファをセット
				stride = sizeof(int);
				offset = 0;
				pContext->IASetIndexBuffer(pFbxModel->GetIndexBufferAt(i).Get(), DXGI_FORMAT_R32_UINT, 0);

				// コンスタントバッファをセット
				pContext->VSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
				pContext->PSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用

				if (hTexture)
				{
					constantBuffer.hasTexture = TRUE;
					Texture* pTexture{ resource.GetTexture(hTexture) };
					wassert(pTexture != nullptr);
					if (pTexture)
					{
						ID3D11SamplerState* pSampler{ pTexture->GetSamplerState() };
						pContext->PSSetSamplers(0, 1, &pSampler);

						ID3D11ShaderResourceView* pSRV{ pTexture->GetShaderResourceView() };
						pContext->PSSetShaderResources(0, 1, &pSRV);
					}
				}
				else
				{
					constantBuffer.hasTexture = FALSE;
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

				#if WTGB_CPMR_USE_VERTEX_LOG
				{
					size_t vertexCount = pFbxModel->GetVertexCount();
					std::vector<Fbx::Vertex> vertexes{};
					vertexes.resize(vertexCount);

					// 1. 元バッファの情報取得
					D3D11_BUFFER_DESC desc{};
					pFbxModel->GetVertexBuffer()->GetDesc(&desc);

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
					pContext->CopyResource(pStagingBuffer.Get(), pFbxModel->GetVertexBuffer().Get());

					// 5. ステージングバッファをマップしてCPUで読み込み
					D3D11_MAPPED_SUBRESOURCE mapped{};
					hr = pContext->Map(pStagingBuffer.Get(), 0, D3D11_MAP_READ, 0, &mapped);
					if (SUCCEEDED(hr))
					{
						// バッファの内容をコピー
						memcpy(vertexes.data(), mapped.pData, sizeof(Fbx::Vertex) * vertexCount);
						pContext->Unmap(pStagingBuffer.Get(), 0);
					}

					LOGFLN("----------------------------");
					for (auto& vertex : vertexes)
					{
						LOGFLN("UV:({},{})", vertex.uv.m128_f32[0], vertex.uv.m128_f32[1]);
					}

					pStagingBuffer.Reset();
				}
				#endif
			}
		});
}
