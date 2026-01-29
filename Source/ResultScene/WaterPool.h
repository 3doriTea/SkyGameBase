#pragma once
#include <wtgb.h>
#include "WaterPlane/WaterMesh.h"


/// <summary>
/// 水面プール
/// </summary>
class WaterPool : public GameObject
{
public:
	WaterPool();
	~WaterPool();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 指定した座標のy軸上でステージ面のy座標を取得する
	/// </summary>
	/// <param name="_worldPosition">ワールド座標</param>
	/// <returns>ステージのy座標</returns>
	float GetPosY(const Vector3& _worldPosition) { return 0.0f; wassert(false); }

	/// <summary>
	/// ステージのxzサイズを取得する
	/// </summary>
	/// <returns>xzサイズ</returns>
	Vector2 GetSizeXZ() const
	{
		return
		{
			verticesDistance_.x * (verticesCount_.x - 1),
			verticesDistance_.y * (verticesCount_.y - 1)
		};
	}

private:
	/// <summary>
	/// パラメータを読み込む
	/// </summary>
	/// <param name="_json">パラメータのjson</param>
	void OnLoadParam(const json& _json);

private:
	Vector2 verticesDistance_;     // 各頂点間の距離
	Vector2Int verticesCount_;     // xz面の頂点数
	std::vector<float> points_;    // 各頂点の高さ (y軸だけの情報)
	WaterMesh waterMesh_;          // ステージのメッシュ情報
};
