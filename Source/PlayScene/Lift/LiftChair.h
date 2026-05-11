#pragma once
#include <wtgb.h>

/// <summary>
/// リフトのかごである椅子オブジェクト
/// </summary>
class LiftChair : public GameObject
{
public:
	LiftChair(const EntityId _structure, const float _beginLength, const float _maxLength);
	~LiftChair();

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

	/// <summary>
	/// パラメータ読み込み
	/// </summary>
	/// <param name="_json">パラメータjson</param>
	void OnLoadParam(const json& _json);

private:
	EntityId structure_;     // リフト本体
	float length_;           // 再生中の長さ
	float lengthMax_;        // 全体の長さ
	float moveSpeedPerSec_;  // 1秒間あたりの移動スピード
};
