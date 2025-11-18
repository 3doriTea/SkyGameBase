#pragma once
#include "pch/pch.h"
#include "CommonGameComponent.h"
#include "GameSystem/CPModelMesh.h"
#include "GameSystem/ModelMesh/IMeshSimple.h"

namespace wtgb
{

	class COMPONENT(ModelMesh)
	{
	public:
		/// <summary>
		/// モデルメッシュの種類
		/// </summary>
		enum struct Type
		{
			Other,       // その他知らない
			Fbx,         // FBX
			SimpleMesh,  // シンプルなメッシュ描画
		};

		friend class CPMeshRenderer;
	public:
		class SETTER(ModelMesh)
		{
			SETTER_HEAD(ModelMesh)

			SETTER_PARAM(std::string, fileName)
			SETTER_PARAM(std::string, pOriginalMesh)
		};

	public:
		ModelMesh();
		~ModelMesh() {}

		void Init(ViewerCached system_) override;
		void Update(ViewerCached system_) override {}
		void End() override;

	private:
		std::string fileName_;  // モデルのファイル名
		IMeshSimple* pOriginalMesh_;  // シンプルならオリジナルメッシュ

		ModelHandle hModel_;  // モデルハンドル

		Type modelMeshType_;  // モデルメッシュの種類
	};
}
