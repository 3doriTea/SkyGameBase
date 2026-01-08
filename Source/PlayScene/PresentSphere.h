#pragma once
#include <wtgb.h>

class PresentSphere : public GameObject
{
public:
	PresentSphere(const EntityId _player, const Vector3& _position, const Vector3& _dropPosition);
	~PresentSphere();

	void Init() override;
	void Update() override;
	void Release() override;

	/// <summary>
	/// 跳ね返りが起きたかを取得する 取得後はリセットされる
	/// </summary>
	/// <returns></returns>
	inline bool IsBounded() const { return isBounded_; }

	/// <summary>
	/// プレゼントが取られたか
	/// </summary>
	/// <returns>取られた true / false</returns>
	inline bool IsHit() const { return isHitted_; }

private:
	bool isBounded_;   // 跳ね返りが起きたか
	//bool isBounding_;  // 跳ね返りが起きているか
	//float timeLeft_;   // 止まるまでの残り時間
	//bool isStopping_;  // 跳ね返りが終わり止まっているか

	bool isHitted_;    // プレイヤーと当たった

	EntityId player_;  // プレイヤー
};
