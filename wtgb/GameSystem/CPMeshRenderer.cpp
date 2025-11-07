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
	ID3D11DeviceContext* pContext{ System().Get<Direct3D>().Resource().Context() };
	for (auto itr = this->begin(); itr != this->end(); itr++)
	{
		size_t index{ itr.GetIndex() };
		EntityId entityId{ System().Get<CPGameObject>().GetEntityId(index) };
		ModelHandle hModel{ System().Get<CPModelMesh>().Get(entityId)->hModel_ };
		Transform* pTransform{ System().Get<CPTransform>().Get(entityId) };

		if (pTransform == nullptr)
		{
			wassert(false && "Transformの取得に失敗");
			continue;
		}

		Model& model{ System().Get<Model>() };
		ModelResource* pModel{ model.GetModel(hModel) };
		Fbx* pFbxModel{ dynamic_cast<Fbx*>(pModel) };
		if (pFbxModel == nullptr)
		{
			LOGFLN("Warn:Fbx以外のモデルが読み込まれた！");
			return;
		}

		Fbx::ConstantBuffer constantBuffer{};
		constantBuffer.matWVP = XMMatrixTranspose(pTransform->GetWorldMatrix() * camera.GetViewMatrix() * camera.GetProjectionMatrix());
		constantBuffer.matNormal = XMMatrixTranspose(pTransform->GetNormalMatrix());

		// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
		System().Get<Direct3D>().SetShader((*itr).hShader_);

		UINT stride{ sizeof(Fbx::Vertex) };
		UINT offset{ 0 };
		// 頂点バッファをセット
		pContext->IASetVertexBuffers(0, 1, pFbxModel->GetVertexBuffer().GetAddressOf(), &stride, &offset);

		// 各マテリアル分
		for (int i = 0; i < pFbxModel->GetMaterialCount(); i++)
		{
			constantBuffer.diffuse = pFbxModel->GetMaterialAt(i).diffuse;
			constantBuffer.materialFLag = pFbxModel->GetMaterialAt(i).textureFile != "";

			// インデックスバッファをセット
			stride = sizeof(int);
			offset = 0;
			pContext->IASetIndexBuffer(pFbxModel->GetIndexBufferAt(i).Get(), DXGI_FORMAT_R32_UINT, 0);

			// コンスタントバッファをセット
			pContext->VSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // 頂点シェーダ用
			pContext->PSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());  // ピクセルシェーダ用

			if (constantBuffer.materialFLag)
			{
				Texture* pTexture{ System().Get<ResourceSystem>().GetTexture((*itr).hTexture_) };
				wassert(pTexture != nullptr);
				if (pTexture)
				{
					ID3D11SamplerState* pSampler{ pTexture->GetSamplerState() };
					pContext->PSSetSamplers(0, 1, &pSampler);

					ID3D11ShaderResourceView* pSRV{ pTexture->GetShaderResourceView() };
					pContext->PSSetShaderResources(0, 1, &pSRV);
				}
			}

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
}
