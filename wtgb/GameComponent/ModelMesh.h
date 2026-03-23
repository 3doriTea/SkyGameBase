#pragma once
#include "pch/pch.h"
#include "Helper/CommonGameComponent.h"
#include "GameSystem/ModelMesh/IMeshSimple.h"
#include "GameSystem/ModelMesh/IMeshesSimple.h"
#include "GameSystem/CPModelMesh.h"


namespace wtgb
{

	class COMPONENT(ModelMesh)
	{
		COMPONENT_HEAD(ModelMesh)
	public:
		/// <summary>
		/// モデルメッシュの種類
		/// </summary>
		enum struct Type
		{
			Other,         // その他知らない
			Fbx,           // FBX
			SimpleMesh,    // シンプルなメッシュ描画
			SimpleMesh2D,  // シンプルなメッシュ2D描画
			FbxBack,       // 最背面に描画したいFBX
			FbxAplha,      // 透明度を適用したいFBX
			SimpleMeshes,  // シンプルなメッシュ群描画
			SimpleMeshUI3D,  // シンプルなメッシュUI3D描画 透過する
		};

		friend class CPMeshRenderer;
	public:
		class SETTER(ModelMesh)
		{
			SETTER_HEAD(ModelMesh)

			SETTER_PARAM(std::string, fileName)
			SETTER_PARAM_PTR(IMeshSimple, pOriginalMesh)
			SETTER_PARAM_PTR(IMeshesSimple, pOriginalMeshes)
			SETTER_PARAM(Type, modelMeshType)
		};

	public:
		ModelMesh();
		~ModelMesh() {}

		void Init(ViewerCached system_) override;
		void Update(ViewerCached system_) override {}
		void End() override;

		/// <summary>
		/// モデルメッシュの種類を取得
		/// </summary>
		/// <returns>モデルメッシュの種類</returns>
		Type GetType() const { return modelMeshType_; }

	private:
		std::string fileName_;  // モデルのファイル名

		IMeshSimple* pOriginalMesh_;      // シンプルならオリジナルメッシュ
		IMeshesSimple* pOriginalMeshes_;  // シンプルならオリジナルメッシュ
		
		ModelHandle hModel_;  // モデルハンドル
		Type modelMeshType_;  // モデルメッシュの種類
	};
}
