#pragma once
#include <wtgb.h>

class PresentSphere : public GameObject
{
public:
	PresentSphere(const EntityId _player, const Vector3& _position);
	~PresentSphere();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// プレゼントが取られたか
	/// </summary>
	/// <returns>取られた true / false</returns>
	bool IsHit() const { return isHitted_; }

private:
	bool isBounding_;  // 跳ね返りが起きているか
	float timeLeft_;   // 止まるまでの残り時間
	bool isStopping_;  // 跳ね返りが終わり止まっているか

	bool isHitted_;    // プレイヤーと当たった

	EntityId player_;  // プレイヤー
};
