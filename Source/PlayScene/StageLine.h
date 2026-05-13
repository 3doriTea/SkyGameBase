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

	/// <summary>
	/// ストッパー開始地点のz座標を取得
	/// </summary>
	/// <returns>ストッパー開始地点のz座標</returns>
	inline float GetStopperStartPosZ() const { return stopperStartPosZ_; }

	/// <summary>
	/// スタート土台の開始高さ Y座標 を取得する
	/// </summary>
	/// <returns>高さ Y座標</returns>
	inline float GetStartBeginPosY() const { return startBasePosY_; }
	/// <summary>
	/// スタート土台の開始地点 Z座標 を取得する
	/// </summary>
	/// <returns>地点 Z座標</returns>
	inline float GetStartBeginPosZ() const { return startBasePosZ_; }

	inline const std::vector<Vector2>& GetPoints() { return points_; }

private:
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	StageMeshes stageMesh_;        // ステージのメッシュ情報
	float stopperStartPosZ_;       // ストッパー開始地点のz座標
	float startBasePosY_;         // スタート土台の開始地点 Z
	float startBasePosZ_;         // スタート土台の高さ Y
	float textureScale_;           // 地形のテクスチャスケール
	StageLineConfig config_;       // ステージラインの設定
	//StageMeshes stageMesh_;      // ステージメッシュ
	uint32_t startBaseIndex_;      // スタート土台の角っこにあたる頂点インデクス
};
