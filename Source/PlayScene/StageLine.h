#pragma once
#include <wtgb.h>
#include "StageMesh/StageMesh.h"
#include "StageMesh/StageMeshes.h"
#include "StageLineConfig.h"


/// <summary>
/// ステージの面
/// </summary>
class StageLine : public GameObject
{
public:
	StageLine(const StageLineConfig& _config);
	~StageLine();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 指定した座標のy軸上でステージ面のy座標を取得する
	/// </summary>
	/// <param name="_worldPosition">ワールド座標</param>
	/// <returns>ステージのy座標</returns>
	float GetPosY(const Vector3& _worldPosition);

	/// <summary>
	/// ステージのZ軸の長さを取得
	/// </summary>
	/// <returns>ステージのZ軸長さ m</returns>
	float GetStageLengthZ() const;

	inline const std::vector<Vector2>& GetPoints() { return points_; }

private:
	/// <summary>
	/// ステージの点を生成する
	/// </summary>
	bool GenerateStagePoints();

private:
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	StageMeshes stageMesh_;        // ステージのメッシュ情報
	float textureScale_;           // 地形のテクスチャスケール
	StageLineConfig config_;       // ステージラインの設定
};
