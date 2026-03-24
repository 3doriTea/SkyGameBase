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
	pOriginalMeshes_{ nullptr },
	modelMeshType_{ Type::Other }
{}

void wtgb::ModelMesh::Init(ViewerCached system_)
{
	Reflesh(system_);
}

void wtgb::ModelMesh::End()
{
}

void wtgb::ModelMesh::Reflesh(ViewerCached system_)
{
	// ファイル名だけ指定されている
	if (!fileName_.empty() && (!pOriginalMesh_ && !pOriginalMeshes_))
	{
		if (modelMeshType_ == Type::FbxBack  // 最背面に描画したい
			|| modelMeshType_ == Type::FbxAplha)  // 透明度を付けて描画したい
		{
		}
		else
		{
			// ファイル名が指定されている かつ オリジナルメッシュが指定されてない
			modelMeshType_ = Type::Fbx;
		}
	}
	else if (fileName_.empty() && (pOriginalMesh_ || pOriginalMeshes_))
	{
		// ファイル名が指定されていない かつ オリジナルメッシュが指定されている
		if (pOriginalMesh_)
		{
			modelMeshType_ = Type::SimpleMesh;
		}
		else
		{
			modelMeshType_ = Type::SimpleMeshes;
		}
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
	case wtgb::ModelMesh::Type::FbxAplha:  // 透明度を指定したいFBX
		hModel_ = system_.Get<Model>().Load(fileName_);
		break;
	case wtgb::ModelMesh::Type::SimpleMesh:
	case wtgb::ModelMesh::Type::SimpleMeshes:
		//pOriginalMesh_->CallInit();
		break;
	case wtgb::ModelMesh::Type::Other:
	default:
		wassert(false && "未対応のメッシュタイプ");
		break;
	}
}

void wtgb::ModelMesh::SetModel(const ModelHandle _hModel)
{
	hModel_ = _hModel;
}
