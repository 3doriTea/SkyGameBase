#pragma once
#include <wtgb.h>

class ICameraMove;

class CameraController : public GameObject
{
public:
	enum struct Mode
	{
		Free,  // 自由移動
		Play,  // プレイする
	};

public:
	CameraController();
	~CameraController();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// カメラモードをセットする
	/// </summary>
	/// <param name="_mode">カメラモード</param>
	void SetMode(const Mode _mode);

	/// <summary>
	/// 現在のカメラモードを取得する
	/// </summary>
	/// <returns></returns>
	inline Mode GetMode() const { return mode_; }

private:
	EntityId lookTarget_;  // カメラの注視点となるターゲットエンティティ

	Mode mode_;

	Vector2Int prevMousePos_;  // 前フレームのマウススクリーン座標

	ICameraMove* pCameraMove_;  // カメラの移動方法
};
