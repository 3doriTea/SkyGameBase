#pragma once
#include "Helper/CommonGameComponent.h"
#include "GameSystem/ResourceSystem/TextureConfig.h"
#include "GameSystem/CPMeshRenderer.h"


namespace wtgb
{
	class COMPONENT(MeshRenderer)
	{
		friend class ModelMesh;
		COMPONENT_HEAD(MeshRenderer)
	public:
		class SETTER(MeshRenderer)
		{
			SETTER_HEAD(MeshRenderer)

			SETTER_PARAM(std::string, shader)
			SETTER_PARAM(std::string, texture)
			SETTER_PARAM(TextureConfig, textureConfig)
			SETTER_PARAM(D3D11_CULL_MODE, cullMode)
			SETTER_PARAM(D3D11_FILL_MODE, fillMode)
		};

	public:	
		MeshRenderer();
		~MeshRenderer() {}

		void Init(ViewerCached _system) override;
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// テクスチャをセットする
		/// </summary>
		/// <param name="_hTexture">テクスチャのハンドル</param>
		inline void SetTexture(const TextureHandle _hTexture) { hTexture_ = _hTexture; }

	private:
		std::string shader_;
		std::string texture_;
		D3D11_CULL_MODE cullMode_;  // カリングモード
		D3D11_FILL_MODE fillMode_;  // 塗りつぶしモード

		ShaderHandle  hShader_;
		TextureHandle hTexture_;

		TextureConfig textureConfig_;
	};
}
