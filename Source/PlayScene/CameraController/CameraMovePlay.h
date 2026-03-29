#pragma once
#include "ICameraMove.h"

/// <summary>
/// カメラの移動方法 - ゲームプレイ
/// </summary>
class CameraMovePlay : public ICameraMove
{
private:
	enum struct ControlMode
	{
		MoveView,    // 視点移動
		MovePlayer,  // プレイヤー操作
	};

public:
	CameraMovePlay();
	~CameraMovePlay() {}

	void Start(GameObjectReference _ref) override;
	void Update(GameObjectReference _ref) override;
	void End(GameObjectReference _ref) override;

private:
	Vector2Int previous_;   // 前回のマウス座標
	Vector2Int diffValue_;  // 全体的な移動差分

	float angleX_;  // x軸の回転角度
	float angleY_;  // y軸の回転角度
	bool isDragging_;          // マウスがドラッグ中か
	ControlMode controlMode_;  // マウスをドラッグ中の操作モード

	float emphasisBoost_;  // バウンドしたときの衝撃を加算する
	float emphasisPrevYOffset_;  // 前フレームのy軸オフセット

	struct
	{
		float responseRatio = 0.5f;
		float boostThreshold = 15.0f;  // バウンドした判定
		float boostValue = 0.3f;  // バウンドして衝撃の加算値
		float boostDecayRatePerSec = 0.1f;  // 減衰値 (/sec)
		float velocityMin = -10.0f;
		float velocityMax = 10.0f;
	} emphasis_;  // 強調されたカメラ

	Vector3 bounceImpactIntensity_;  // バウンド衝撃-各軸の揺れの強さ
	Vector3 bounceImpactPlayRatio_;  // バウンド衝撃-各軸の再生レート

	struct
	{
		Vector3 frequencyPerSec = Vector3::One() * 2.0f;  // 揺れる往復数(/sec)
		Vector3 startIntensity = Vector3::One() * 3.0f;   // 開始時の揺れ幅
		float dampingRatioPerSec = 0.3f;  // 減衰率(/sec)(0.0で止まらない, 1.0ですぐ止まる)
	} bounceImpact_;

	struct
	{
		int screenDiffMin = -50;
		int screenDiffMax = 50;
	} dragArrow_;

	EntityId stageLine_;  // ステージラインのエンティティ
};
