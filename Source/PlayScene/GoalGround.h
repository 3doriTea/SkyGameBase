#pragma once
#include <wtgb.h>


/// <summary>
/// 曲の再生が終わると現れるゴール
/// </summary>
class GoalGround : public GameObject
{
public:
	GoalGround(const Vector3& _position);
	~GoalGround();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	std::string targetName_;
	EntityId target_;     // ゴールを支援するターゲット
	EntityId playStater_;  // プレイ状態を管理するやつ
};

