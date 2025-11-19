#pragma once
#include <wtgb.h>
#include "StageMesh/StageMesh.h"


class StageLine : public GameObject
{
public:
	StageLine();
	~StageLine();

	void Init() override;
	void Update() override;

private:
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	StageMesh stageMesh_;  // ステージのメッシュ情報
};
