#pragma once
#include <wtgb/wtgb.h>

class Player : public GameObject
{
public:
	Player(const EntityId _parentId, const Vector3 _localPos);
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
	void OnLoadParam(json& _json);

private:
	float angle_;
	float awakeTimeLeft_;  // シーン読み込み直後のラグを待つカウントダウンタイマ
};
