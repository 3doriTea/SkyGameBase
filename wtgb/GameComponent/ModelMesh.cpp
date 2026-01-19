#include "pch/pch.h"
#include "ModelMesh.h"
#include "GameSystem/Model.h"
#include "GameSystem/CPMeshRenderer.h"
#include "WTGBAssert.h"
#include "GameSystem/CPModelMesh.h"

wtgb::ModelMesh::ModelMesh() : 
	hModel_{ INVALID_HANDLE },
	fileName_{},
	pOriginalMesh_{ nullptr },
	modelMeshType_{ Type::Other }
{}

void wtgb::ModelMesh::Init(ViewerCached system_)
{
	if (!fileName_.empty() && pOriginalMesh_ == nullptr)
	{
		if (modelMeshType_ == Type::FbxBack)
		{
			// Fbxの指定だけど最背面に描画したい
			modelMeshType_ = Type::FbxBack;
		}
		else
		{
			// ファイル名が指定されている かつ オリジナルメッシュが指定されてない
			modelMeshType_ = Type::Fbx;
		}
	}
	else if (fileName_.empty() && pOriginalMesh_ != nullptr)
	{
		// ファイル名が指定されていない かつ オリジナルメッシュが指定されている
		modelMeshType_ = Type::SimpleMesh;
	}
	else
	{
		// その他 知らない
		modelMeshType_ = Type::Other;
	}

	// モデルメッシュの種類
	switch (modelMeshType_)
	{
	case wtgb::ModelMesh::Type::Fbx:
	case wtgb::ModelMesh::Type::FbxBack:  // 最背面描画用のFBX
		hModel_ = system_.Get<Model>().Load(fileName_);
		break;
	case wtgb::ModelMesh::Type::SimpleMesh:
		//pOriginalMesh_->CallInit();
		break;
	case wtgb::ModelMesh::Type::Other:
	default:
		wassert(false && "未対応のメッシュタイプ");
		break;
	}
}

void wtgb::ModelMesh::End()
{
}
