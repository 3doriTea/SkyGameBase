#pragma once
#include "ICameraMove.h"

/// <summary>
/// カメラ移動方法 - 自由
/// </summary>
class CameraMoveFree : public ICameraMove
{
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
	float speedBoost_;         // 左シフトキー押しながらで加速する倍率
};
