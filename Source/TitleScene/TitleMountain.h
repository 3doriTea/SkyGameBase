#pragma once
#include <wtgb.h>
#include "PlayScene/StageMesh/StageMesh.h"


/// <summary>
/// タイトルシーンに出てくる山
/// </summary>
class TitleMountain : public GameObject
{
public:
	TitleMountain();
	~TitleMountain() {}

	void Init() override;
	void Update() override {}
	void Release() override {}

private:
	StageMesh stageMesh_;        // 地形メッシュ
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	float textureScale_;           // テクスチャを貼り付ける横の大きさ
};
