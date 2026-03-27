#pragma once
#include <wtgb/wtgb.h>
#include "PlayerTargetting.h"


class ISpeedController;


/// <summary>
/// プレイヤー
/// </summary>
class Player : public GameObject
{
public:
	Player(
		const EntityId _parentId,
		const Vector3 _localPos,
		const EntityId _playState);
	~Player() = default;

	void Init() override;
	void Update() override;
	inline void Release() override {}

	/// <summary>
	/// プレイヤーを移動させる
	/// </summary>
	/// <param name="_move">移動</param>
	void AddMove(const Vector3 _move);

private:
	void OnLoadParam(const json& _json);

	/// <summary>
	/// アニメーションの更新処理
	/// </summary>
	/// <returns>更新処理が発生 true / false</returns>
	bool UpdateAnim();

	/// <summary>
	/// ステージ外に出ないよう横壁でバウンドする処理
	/// </summary>
	/// <returns>バウンドが発生 true / false</returns>
	bool OutBounce();

	/// <summary>
	/// 下山スタートした瞬間の処理
	/// </summary>
	void OnStart();

	/// <summary>
	/// 地面に当たったときの回転をかける処理
	/// </summary>
	/// <returns>回転処理が走った true / false</returns>
	bool GroundBounceRotation();
	
	/// <summary>
	/// カウントダウンを待っているか
	/// </summary>
	/// <returns>待っている true / false</returns>
	bool HasWaitingCountDown();

	/// <summary>
	/// 試しにキャラエッグへのフォーカス処理をする
	/// </summary>
	/// <returns>フォーカス処理が行われた true / false</returns>
	bool TryFocusToCharaEgg();

private:
	PlayerTargeting playerTargeting_;  // プレイヤーターゲティング処理
	bool isTargeting_;                 // ターゲットがあるか
	float toTargetTime_;               // ターゲットに当たるまでの時間
	float angle_;

	float awakeTimeLeft_;         // シーン読み込み直後のラグを待つカウントダウンタイマ
	EntityId playState_;          // プレイ状態
	float startLineZ_;            // 下山開始のライン z座標
	float startDushForce_;        // 開始ダッシュで押す力
	float aboutCircleThreshold_;  // 大体の円の判定 cosθ の値
	
	float slideVeloDampingPerSec_;  // 1秒間あたりのスライド速度の抵抗

	float slideVelocityX_;        // 横スライド速度
	float rotateBoostSpeedX_;     // x軸での回転速度ブースト
	float bounceRotationVZDiv_;   // 速度.zに比例する回転速度の分母
	float onGroundRotationVelo_;  // 地上に引っ付いている時の最大回転速度
	float colliderRadius_;        // 当たり判定円の半径

	struct
	{
		float totalTime;  // 総アニメーション時間
		float playTime;   // 現在の再生時間
	} boundXAnim;         // x軸のバウンドアニメーション
};
