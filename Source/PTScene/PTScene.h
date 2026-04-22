#pragma once
#include <wtgb.h>
#include "PerformanceTester.h"

/// <summary>
/// パフォーマンスをテストするシーン
/// </summary>
class PTScene : public GameScene
{
public:
	PTScene(GameScene::Config&& _config);
	~PTScene();

	/// <summary>
	/// シーン開始時に呼ばれる処理
	/// </summary>
	void Start() override;
	/// <summary>
	/// フレーム更新時の処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 出現している球体の数を取得する
	/// </summary>
	/// <returns>球体の数</returns>
	inline uint32_t GetSphereCount() const { return sphereCount_; }

private:
	/// <summary>
	/// 球を配置する座標を取得する
	/// </summary>
	/// <returns></returns>
	Vector3 GetInstancePositionSphere();

private:
	float animationTime_;   // アニメーション時間
	uint32_t sphereCount_;  // 球体の数
};
