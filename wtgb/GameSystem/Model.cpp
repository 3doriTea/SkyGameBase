#include "pch\pch.h"
#include "Model.h"
#include "ModelMesh/Fbx.h"
#include "WTGBAssert.h"

wtgb::Model::Model()
{
}

wtgb::Model::~Model()
{
}

wtgb::Result wtgb::Model::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::Model::Update(const ViewerUpdate& _system)
{
}

void wtgb::Model::End()
{
}

void wtgb::Model::Load(const std::string& _fileName)
{
	ModelHandle hModel{ models_.Emplace(new Fbx{}) };
	HRESULT hResult{};
	hResult = models_.At(hModel).TryLoad(_fileName);
	wassert(SUCCEEDED(hResult) && "ÉÇÉfÉãÇÃì«Ç›çûÇ›Ç…é∏îs");
}
