#pragma once
#include <wtgb.h>


/// <summary>
/// リフト追従オブジェクト : 雲
/// </summary>
class Cloud : public GameObject
{
public:
	Cloud(const EntityId _parentLift);
	~Cloud();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	void OnLoadParam(const json& _json);

private:
	EntityId parentLift_;  // くっつく椅子
	Vector3 randomBegin_;  // ランダム範囲開始点
	Vector3 randomEnd_;    // ランダム範囲終了点
};
