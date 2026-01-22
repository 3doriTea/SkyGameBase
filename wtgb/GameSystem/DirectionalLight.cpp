#include "DirectionalLight.h"


wtgb::DirectionalLight::DirectionalLight() :
	direction_{ 0, -1, 0 },
	color_{ 0xffffff }
{
}

wtgb::DirectionalLight::~DirectionalLight()
{
}

wtgb::Result wtgb::DirectionalLight::Init(const ViewerInit& _viewer)
{
	return Result::Code::Ok;
}

void wtgb::DirectionalLight::End()
{
}
