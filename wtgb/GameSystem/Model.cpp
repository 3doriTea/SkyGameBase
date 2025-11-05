#include "pch\pch.h"
#include "Model.h"
#include "ModelMesh/Fbx.h"
#include "WTGBAssert.h"

wtgb::Model::Model() :
	system_{ nullptr }
{
}

wtgb::Model::~Model()
{
}

wtgb::Result wtgb::Model::Init(const ViewerInit& _viewer)
{
	system_ = _viewer.GetCache();
	return Result::Code::Ok;
}

void wtgb::Model::Update(const ViewerUpdate& _system)
{
}

void wtgb::Model::End()
{
	models_.Release([](ModelResource*& modelResource)
		{
			modelResource->CallRelease();
		});
}

wtgb::ModelHandle wtgb::Model::Load(const std::string& _fileName)
{
	ModelHandle hModel{ models_.Emplace(new Fbx{ _fileName, system_ }) };
	HRESULT hResult{};
	models_.At(hModel).CallInit();

	return hModel;
}

wtgb::ModelResource* wtgb::Model::GetModel(ModelHandle _hModel)
{
	wtgb::ModelResource* pModel{ &models_.At(_hModel) };
	return pModel;
}
