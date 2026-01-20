#pragma once
#include <wtgb/wtgb.h>
#include "PlayerTargetting.h"

class Player : public GameObject
{
public:
	Player(
		const EntityId _parentId,
		const Vector3 _localPos,
		const EntityId _playState);
	~Player();

	void Init() override;
	void Update() override;
	void Release() override {}

	/// <summary>
	/// プレイヤーを移動させる
	/// </summary>
	/// <param name="_move">移動</param>
	void AddMove(const Vector3 _move);

private:
	void OnLoadParam(const json& _json);

private:
	PlayerTargetting playerTargetting_;  // プレイヤーターゲティング処理
	bool isTargetting_;   // ターゲットがあるか
	float toTargetTime_;  // ターゲットに当たるまでの時間
	float angle_;
	float awakeTimeLeft_;  // シーン読み込み直後のラグを待つカウントダウンタイマ
	EntityId playState_;   // プレイ状態
	float startLineZ_;     // 下山開始のライン z座標
};
