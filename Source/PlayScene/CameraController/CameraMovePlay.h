#pragma once
#include "ICameraMove.h"

/// <summary>
/// カメラの移動方法 - ゲームプレイ
/// </summary>
class CameraMovePlay : public ICameraMove
{
private:
	enum struct ControlMode
	{
		MoveView,    // 視点移動
		MovePlayer,  // プレイヤー操作
	};

public:
	CameraMovePlay() {}
	~CameraMovePlay() {}

	void Start(GameObjectReference _ref) override;
	void Update(GameObjectReference _ref) override;
	void End(GameObjectReference _ref) override;

private:
	bool isDragging_;          // マウスがドラッグ中か
	ControlMode controlMode_;  // マウスをドラッグ中の操作モード
};
