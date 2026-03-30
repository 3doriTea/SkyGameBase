#pragma once
#include "../JsonUnitLoaderBase.h"
#include "WorldConfig.h"


/// <summary>
/// ワールド設定読み込む
/// </summary>
class WorldConfigJsonLoader : public JsonUnitLoaderBase<WorldConfig>
{
public:
	WorldConfigJsonLoader();
	~WorldConfigJsonLoader() = default;

	void OnLoad(const json& _json, WorldConfig* pWorldConfig) override;
};
