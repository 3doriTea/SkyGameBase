#pragma once
#include "../JsonUnitLoaderBase.h"
#include "WorldConfig.h"

class WorldConfigJsonLoader : public JsonUnitLoaderBase<WorldConfig>
{
public:
	WorldConfigJsonLoader();

	void OnLoad(const json& _json, WorldConfig* pWorldConfig) override;
};
