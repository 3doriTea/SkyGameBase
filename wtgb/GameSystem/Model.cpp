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
	models_.Release([this](ModelResource*& modelResource)
		{
			modelResource->CallRelease(system_);
		});
}

wtgb::ModelHandle wtgb::Model::Load(const std::string& _fileName)
{
	std::string_view fileName{ _fileName };

	ModelHandle foundHandle
	{
		models_.GetContainsDuplicate([&fileName](ModelResource*& _pModelResource) -> bool
			{
				return _pModelResource->FileName() == fileName;
			})
	};

	if (foundHandle != INVALID_HANDLE)
	{
		// Šù‚É“Ç‚İ‚İÏ‚İ‚È‚ç‚»‚Ìƒnƒ“ƒhƒ‹‚ğ•Ô‚·
		return foundHandle;
	}

	ModelHandle hModel{ models_.Emplace(new Fbx{ _fileName }) };
	HRESULT hResult{};
	models_.At(hModel).CallInit(system_);

	return hModel;
}

wtgb::ModelResource* wtgb::Model::GetModel(ModelHandle _hModel)
{
	wtgb::ModelResource* pModel{ &models_.At(_hModel) };
	return pModel;
}
