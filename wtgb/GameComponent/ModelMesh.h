#pragma once
#include "pch/pch.h"
#include "Helper/CommonGameComponent.h"
#include "GameSystem/ModelMesh/IMeshSimple.h"

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
			SImpleMesh2D,  // シンプルなメッシュ2D描画
		};

		friend class CPMeshRenderer;
	public:
		class SETTER(ModelMesh)
		{
			SETTER_HEAD(ModelMesh)

			SETTER_PARAM(std::string, fileName)
			SETTER_PARAM_PTR(IMeshSimple, pOriginalMesh)
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
		IMeshSimple* pOriginalMesh_;  // シンプルならオリジナルメッシュ

		ModelHandle hModel_;  // モデルハンドル

		Type modelMeshType_;  // モデルメッシュの種類
	};
}
