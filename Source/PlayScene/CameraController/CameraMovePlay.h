#pragma once
#include "ICameraMove.h"

/// <summary>
/// カメラの移動方法 - ゲームプレイ
/// </summary>
class CameraMovePlay : public ICameraMove
{
public:
	CameraMovePlay() {}
	~CameraMovePlay() {}

	void Start(GameObjectReference _ref) override;
	void Update(GameObjectReference _ref) override;
	void End(GameObjectReference _ref) override;

private:
	
};
