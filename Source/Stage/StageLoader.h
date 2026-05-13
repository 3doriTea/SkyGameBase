#pragma once
#include <wtgb.h>

/// <summary>
/// ステージデータのjsonファイルから頂点を読み取る
/// </summary>
class StageLoader
{
public:
	StageLoader(
		std::vector<Vector2>& _points,
		uint32_t* _pStartBaseEdgeIndex,
		float& _textureScale);
	~StageLoader();

	bool TryLoad(const fs::path& _fileName);

private:
	std::vector<Vector2>& points_;  // 各頂点の情報
	uint32_t* pStartBaseEdgeIndex_;  // スタート土台の崖っぷち頂点インデックス
	float& textureScale_;           // テクスチャの横拡大率
};
