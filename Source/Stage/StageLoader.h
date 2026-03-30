#pragma once
#include <wtgb.h>

/// <summary>
/// ステージデータのjsonファイルから頂点を読み取る
/// </summary>
class StageLoader
{
public:
	StageLoader(std::vector<Vector2>& _points, float& _textureScale);
	~StageLoader();

	bool TryLoad(const fs::path& _fileName);

private:
	std::vector<Vector2>& points_;
	float& textureScale_;
};
