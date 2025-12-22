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

	/// <summary>
	/// リフトが回るスピードを取得する
	/// </summary>
	/// <returns>リフトが1秒間当たりで回る角度</returns>
	float GetRotationSpeedPerSec() const { return rotationSpeedPerSec_; }

	/// <summary>
	/// Z座標からポールの設置座標を取得する
	/// </summary>
	/// <param name="_z">奥行き座標</param>
	Vector3 GetPolePosition(const float _z);

private:
	float rotationSpeedPerSec_;  // リフトが1秒間当たりで回るスピード
	EntityId stage_;  // ステージオブジェクト
};
