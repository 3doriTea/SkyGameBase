#include "WorldConfigJsonLoader.h"

WorldConfigJsonLoader::WorldConfigJsonLoader() :
	JsonUnitLoaderBase{ "PlaySceneWorldConfig.json" }
{
}

void WorldConfigJsonLoader::OnLoad(const json& _json, WorldConfig* pWorldConfig)
{
	*pWorldConfig = std::move(WorldConfig
		{
			.safeZoneXMin = _json.value("safeZoneXMin", 0.0f),
			.safeZoneXMax = _json.value("safeZoneXMax", 400.0f),
			.eggGetDistance = _json.value("eggGetDistance", 10.0f),
			.lightDirection = _json.value("lightDirection", Vector3{ -6.74646f, -15.585419f, 26.661987f }),
			.gravity = _json.value("gravity", 9.8f),
			.lift
			{
				.polePosX = _json.value("/lift/polePosX", 10.0f)
			},
			.player
			{
				.startPositionY = _json.value("/player/startPositionY", 30.0f),
				.startPositionZ = _json.value("/player/startPositionZ", 5.0f),
			},
			.bgmFilePath = _json.value("bgmFilePath", "Sound/entertainer.mid"),
		});
}
