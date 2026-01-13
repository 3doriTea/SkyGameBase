#pragma once
#include <wtgb.h>

class MapView : public GameObject
{
private:
	struct MapPoint
	{
		Vector2Int position;
	};

public:
	MapView();
	~MapView();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	float mapSizePix_;                 // マップのサイズ
	std::vector<MapPoint> mapPoints_;  // マップ上のポイント
};
