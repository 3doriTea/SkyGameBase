#pragma once
#include "ICameraMove.h"

/// <summary>
/// カメラ移動方法 - 自由
/// </summary>
class CameraMoveFree : public ICameraMove
{
private:
	enum struct ControlMode
	{
		MoveView,    // 視点移動
		MovePlayer,  // プレイヤー操作
	};
public:
	CameraMoveFree();
	~CameraMoveFree();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Start(GameObjectReference _ref) override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(GameObjectReference _ref) override;
	/// <summary>
	/// 終了処理
	/// </summary>
	void End(GameObjectReference _ref) override;

private:
	bool isDragging_;          // マウスがドラッグ中か
	ControlMode controlMode_;  // マウスをドラッグ中の操作モード
	float speedBoost_;         // 左シフトキー押しながらで加速する倍率
};
