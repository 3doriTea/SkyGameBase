#include "pch/pch.h"
#include "StageLoader.h"

StageLoader::StageLoader(std::vector<Vector2>& _points, float& _textureScale) :
	points_{ _points },
	textureScale_{ _textureScale }
{
}

StageLoader::~StageLoader()
{
}

bool StageLoader::TryLoad(const fs::path& _fileName)
{
	std::ifstream ifs{ _fileName };
	if (!ifs)
	{
		return false;  // ファイル読み込みに失敗
	}
	json j{};

	ifs >> j;
	ifs.close();

	textureScale_ = j.value("textureScale", 20.0f);

	const size_t POINTS_SIZE{ j["points"].size() };

	points_.resize(POINTS_SIZE);

	// jsonから一部ステージを読み取ってくる
	for (size_t i = 0; i < POINTS_SIZE; i++)
	{
		Vector2 pos
		{
			j["points"][i]["x"].get<float>(),
			j["points"][i]["y"].get<float>()
		};
		points_.push_back(pos);
	}

	return true;
}
