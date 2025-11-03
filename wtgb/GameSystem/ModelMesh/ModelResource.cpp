#include "pch\pch.h"
#include "ModelResource.h"

wtgb::ModelResource::ModelResource(const std::string& _fileName, const ViewerCached _system) :
	FILE_NAME_{ _fileName },
	SYSTEM_{ _system }
{
}
