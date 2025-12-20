#pragma once
#include <wtgb.h>

/// <summary>
/// ステージデータのjsonファイルから頂点を読み取る
/// </summary>
class StageLoader
{
public:
	StageLoader(std::vector<Vector2>& _points);
	~StageLoader();

	bool TryLoad(const fs::path& _fileName);

private:
	std::vector<Vector2>& points_;
};
