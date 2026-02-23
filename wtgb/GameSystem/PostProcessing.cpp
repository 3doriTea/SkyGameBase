#include "PostProcessing.h"
#include "Direct3D.h"


wtgb::PostProcessing::PostProcessing()
{
}

wtgb::PostProcessing::~PostProcessing()
{
}

wtgb::Result wtgb::PostProcessing::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::PostProcessing::Update(const ViewerUpdate& _viewer)
{
	auto& resouce{ _viewer.Get<Direct3D>().Resource() };
	ID3D11Device* pDevice{ resouce.DeviceComPtr().Get() };
	ID3D11DeviceContext* pContext{ resouce.ContextComPtr().Get() };

	pContext->Draw(mesh2d_.GetVertexCount(), 0);
}

void wtgb::PostProcessing::End()
{
}
