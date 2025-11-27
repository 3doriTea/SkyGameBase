#pragma once
#include <wtgb.h>

class CameraController : public GameObject
{
public:
	enum struct Mode
	{
		Free,      // 自由移動
		GamePlay,  // プレイする
	};

public:
	CameraController();
	~CameraController();

	void Init() override;
	void Update() override;
	void Release() override {}

	/// <summary>
	/// カメラモードをセットする
	/// </summary>
	/// <param name="_mode">カメラモード</param>
	void SetMode(const Mode _mode) { mode_ = _mode; }

	/// <summary>
	/// 現在のカメラモードを取得する
	/// </summary>
	/// <returns></returns>
	inline Mode GetMode() const { return mode_; }

private:
	/// <summary>
	/// 自由に動き回る
	/// </summary>
	void UpdateFree();
	/// <summary>
	/// ゲームプレイ時の動き
	/// </summary>
	void UpdateGamePlay();

private:
	EntityId lookTarget_;  // カメラの注視点となるターゲットエンティティ

	Mode mode_;

	float speedBoost_;
	Vector2Int prevMousePos_;  // 前フレームのマウススクリーン座標
};
