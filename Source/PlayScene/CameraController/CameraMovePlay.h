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
	CameraMovePlay();
	~CameraMovePlay() {}

	void Start(GameObjectReference _ref) override;
	void Update(GameObjectReference _ref) override;
	void End(GameObjectReference _ref) override;

private:
	Vector2Int previous_;  // 前回のマウス座標
	Vector2Int diffValue_;  // 全体的な移動差分

	float angleX_;  // x軸の回転角度
	float angleY_;  // y軸の回転角度
	bool isDragging_;          // マウスがドラッグ中か
	ControlMode controlMode_;  // マウスをドラッグ中の操作モード

	EntityId stageLine_;  // ステージラインのエンティティ
};
