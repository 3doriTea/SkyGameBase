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
	/// ƒvƒŒƒCƒ„[‚ğˆÚ“®‚³‚¹‚é
	/// </summary>
	/// <param name="_move">ˆÚ“®</param>
	void AddMove(const Vector3 _move);

private:
	float angle_;
};
