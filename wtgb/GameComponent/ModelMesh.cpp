#include "pch/pch.h"
#include "ModelMesh.h"
#include "GameSystem/Model.h"

wtgb::ModelMesh::ModelMesh() : 
	hModel_{ INVALID_HANDLE }
{}

void wtgb::ModelMesh::Init(ViewerCached system_)
{
	system_.Get<Model>().Load(fileName_);
}
