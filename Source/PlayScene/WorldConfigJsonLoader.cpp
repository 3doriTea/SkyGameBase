#include "WorldConfigJsonLoader.h"

WorldConfigJsonLoader::WorldConfigJsonLoader() :
	JsonUnitLoaderBase{ "PlaySceneWorldConfig.json" }
{
}

void WorldConfigJsonLoader::OnLoad(const json& _json, WorldConfig* pWorldConfig)
{
	// JSONからワールドの設定を読み込んでいく

	*pWorldConfig = std::move(WorldConfig
		{
			.safeZoneXMin = _json.value("safeZoneXMin", 0.0f),
			.safeZoneXMax = _json.value("safeZoneXMax", 400.0f),
			.eggGetDistance = _json.value("eggGetDistance", 10.0f),
			.lightDirection = _json.value("lightDirection", Vector3{ -6.74646f, -15.585419f, 26.661987f }),
			.gravity = _json.value("gravity", 9.8f),
			.lift
			{
				.polePosX = _json.value("/lift/polePosX"_json_pointer, 10.0f)
			},
			.player
			{
				.startPositionY = _json.value("/player/startPositionY"_json_pointer, 30.0f),
				.startPositionZ = _json.value("/player/startPositionZ"_json_pointer, 5.0f),
			},
			.bgmFilePath = _json.value("bgmFilePath", "Sound/entertainer.mid"),
			.stageLineConfig
			{
				.goalHeight = _json.value("/stageLine/goalHeight"_json_pointer, 3000.0f),
				.goalPosY = _json.value("/stageLine/goalPosY"_json_pointer, -3000.0f),
				.randRangeX = _json.value("/stageLine/randRangeX"_json_pointer, 100.0f),
				.randRangeY = _json.value("/stageLine/randRangeY"_json_pointer, 30.0f),
				.goalSizeZ = _json.value("/stageLine/goalSizeZ"_json_pointer, 300.0f),
				.goalWallHeight = _json.value("/stageLine/goalWallHeight"_json_pointer, 300.0f),
				.stageScale = _json.value("/stageLine/stageScale"_json_pointer, Vector3{ 400.0, 1.0, 1.0 }),
				.uvScaleRatioX = _json.value("/stageLine/uvScaleRatioX"_json_pointer, 20.0f),
			}
		});
}
