#pragma once
#include <wtgb/wtgb.h>
#include "PlayerTargetting.h"


class ISpeedController;

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
	PlayerTargeting playerTargeting_;  // プレイヤーターゲティング処理
	bool isTargeting_;                 // ターゲットがあるか
	float toTargetTime_;               // ターゲットに当たるまでの時間
	float angle_;
	float awakeTimeLeft_;       // シーン読み込み直後のラグを待つカウントダウンタイマ
	EntityId playState_;        // プレイ状態
	float startLineZ_;          // 下山開始のライン z座標
	
	float slideVeloDampingPerSec_;  // 1秒間あたりのスライド速度の抵抗

	float slideVelocityX_;        // 横スライド速度
	float rotateBoostSpeedX_;     // x軸での回転速度ブースト
	float bounceRotationVZDiv_;   // 速度.zに比例する回転速度の分母
	float onGroundRotationVelo_;  // 地上に引っ付いている時の最大回転速度
	float colliderRadius_;      // 当たり判定円の半径
};
