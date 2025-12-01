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

	void Start() override;
	void Update(ViewerCached& _system, const EntityId _entityId) override;
	void End() override;

private:
	
};
