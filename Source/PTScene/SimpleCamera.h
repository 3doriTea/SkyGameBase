#pragma once
#include <wtgb.h>

/// <summary>
/// シンプルな自由移動ができるカメラ
/// </summary>
class SimpleCamera : public GameObject
{
public:
	SimpleCamera();
	~SimpleCamera();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Init() override;
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update() override;
	/// <summary>
	/// 解放処理
	/// </summary>
	void Release() override;

private:
	/// <summary>
	/// 固有のパラメータをjsonから読み込む
	/// </summary>
	/// <param name="_json">パラメータのjson</param>
	void OnLoadParam(const json& _json);

	/// <summary>
	/// 座標の更新
	/// </summary>
	/// <returns>更新した true / false</returns>
	bool UpdatePosition();

	/// <summary>
	/// 角度の更新
	/// </summary>
	/// <returns>更新した true / false</returns>
	bool UpdateAngle();

private:
	float moveSpeedPerSec_;  // 1秒間あたりの移動速度
	float moveAnglePerSecRad_;  // 1秒間あたりの回転角速度 (ラジアン)
};
