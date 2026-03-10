#pragma once
#include <wtgb.h>
#include "StageMesh/StageMesh.h"


/// <summary>
/// ステージの面
/// </summary>
class StageLine : public GameObject
{
public:
	StageLine();
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

private:
	std::vector<Vector2> points_;  // 各頂点の座標 (xy平面で考える)
	StageMesh stageMesh_;          // ステージのメッシュ情報
};
