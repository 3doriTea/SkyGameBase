#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPMeshRenderer.h"
#include "GameSystem/ResourceSystem/TextureConfig.h"

namespace wtgb
{
	class COMPONENT(MeshRenderer)
	{
		friend class ModelMesh;
		friend class CPMeshRenderer;
	public:
		class SETTER(MeshRenderer)
		{
			SETTER_HEAD(MeshRenderer)

			SETTER_PARAM(std::string, shader)
			SETTER_PARAM(std::string, texture)
			SETTER_PARAM(TextureConfig, textureConfig)
		};

	public:	
		MeshRenderer();
		~MeshRenderer() {}

		void Init(ViewerCached _system) override;
		void Update(ViewerCached _system) override {}

	private:
		std::string shader_;
		std::string texture_;

		ShaderHandle  hShader_;
		TextureHandle hTexture_;

		TextureConfig textureConfig_;
	};
}
