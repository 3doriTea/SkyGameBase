#include "pch\pch.h"
#include "CPMeshRenderer.h"
#include "GameSystem/Debug.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/CPGameObject.h"
#include "GameSystem/Model.h"
#include "GameSystem/Direct3D.h"
#include "GameSystem/ModelMesh/Fbx.h"
#include "GameSystem/Camera.h"

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

		Model& model{ System().Get<Model>() };
		ModelResource* pModel{ model.GetModel(hModel) };
		Fbx* pFbxModel{ dynamic_cast<Fbx*>(pModel) };
		if (pFbxModel == nullptr)
		{
			LOGFLN("Warn:Fbx以外のモデルが読み込まれた！");
			return;
		}

		Fbx::ConstantBuffer constantBuffer{};
		constantBuffer.matWVP = XMMatrixTranspose(XMMatrixIdentity() * camera.GetViewMatrix() * camera.GetProjectionMatrix());
		constantBuffer.matNormal = XMMatrixTranspose(XMMatrixIdentity());

		// 頂点バッファ、インデックスバッファ、コンスタントバッファ、をパイプラインにセットする
		System().Get<Direct3D>().SetShader((*itr).hShader_);

		UINT stride{ sizeof(Fbx::Vertex) };
		UINT offset{ 0 };
		// 頂点バッファをセット
		pContext->IASetVertexBuffers(0, 1, pFbxModel->GetVertexBuffer().GetAddressOf(), &stride, &offset);

		{
			constantBuffer.diffuse = { 1, 1, 1, 1 };
			constantBuffer.materialFLag = 0;

			pContext->IASetIndexBuffer(pFbxModel->GetIndexBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);

			pContext->VSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());
			pContext->PSSetConstantBuffers(0, 1, pFbxModel->GetConstantBuffer().GetAddressOf());

			if (false)
			{
				ID3D11SamplerState* pSampler{ nullptr };
				pContext->PSSetSamplers(0, 1, &pSampler);

				ID3D11ShaderResourceView* pSRV{ nullptr };
				pContext->PSSetShaderResources(0, 1, &pSRV);
			}

			pContext->DrawIndexed(static_cast<UINT>(pFbxModel->GetIndexCount()), 0, 0);
		}

		// 各マテリアル分
		//for (int i = 0; i < pFbxModel->GetMaterialCount(); i)
		//{
		//	//ID3D11
		//}
	}
}
