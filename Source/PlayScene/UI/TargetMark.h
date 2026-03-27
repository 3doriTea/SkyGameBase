#pragma once
#include <wtgb.h>


using TargetMarkId = uint32_t;

/// <summary>
/// ターゲットにマークを付けるUI
/// </summary>
class TargetMark : public GameObject
{
public:
	TargetMark();
	~TargetMark();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// マークを追加する
	/// </summary>
	/// <param name="_worldPosition">ワールド座標</param>
	/// <returns>追加したマークの識別番号</returns>
	TargetMarkId Add(const Vector3& _worldPosition);

	/// <summary>
	/// 指定したマークのワールド座標をセットする
	/// </summary>
	/// <param name="_id">マークの識別番号</param>
	/// <param name="_worldPosition">ワールド座標</param>
	void SetPosition(const TargetMarkId _id, const Vector3& _worldPosition);

	/// <summary>
	/// 指定したマークを消す
	/// </summary>
	void Remove(const TargetMarkId _id);

private:
	void OnLoadParam(const json& _json);

private:
	std::map<TargetMarkId, Vector3> markIdToPosition_;  // マーク番号と描画座標
	TargetMarkId idCounter_;  // idをカウントするやつ
	TextureHandle hMarkImage_;  // マークの画像ハンドル
};
