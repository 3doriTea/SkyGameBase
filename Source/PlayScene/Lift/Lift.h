#pragma once
#include <wtgb.h>

class Lift : public GameObject
{
public:
	Lift(EntityId _stage);
	~Lift();

	void Init() override;
	void Update() override;
	void Release() override;

private:
	EntityId stage_;  // ステージオブジェクト
};
