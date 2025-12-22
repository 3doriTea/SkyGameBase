#pragma once
#include <wtgb.h>

class Lift : public GameObject
{
public:
	enum LOOP_POLE_TYPE
	{
		LOOP_POLE_UPPER,  // 頂上のポール
		LOOP_POLE_LOWER,  // 麓のポール
		LOOP_POLE_MAX,    // 回転ポールの数
	};
private:
	/// <summary>
	/// リフトの柱
	/// </summary>
	struct Pole
	{
		Pole(const EntityId _entityId);

		EntityId entityId;
	};
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
	/// <summary>
	/// 試しにZ座標からラインの座標を取得する
	/// </summary>
	/// <param name="_z">奥行き座標</param>
	/// <param name="_linePos">ロープのライン座標出力用ポインタ</param>
	/// <returns>範囲内のため取得できた true / false</returns>
	bool TryGetLinePosition(const float _z, Vector3* _pPosition);

	/// <summary>
	/// 両端の回転ポールを取得する
	/// </summary>
	/// <param name="_type">ポールの種類</param>
	/// <returns>ポールのエンティティId</returns>
	EntityId GetLoopPole(const LOOP_POLE_TYPE _type) const { return loopPole_[_type]; }

private:
	float rotationSpeedPerSec_;  // リフトが1秒間当たりで回るスピード
	EntityId stage_;             // ステージオブジェクト
	std::vector<Pole> poles_;    // リフトの全柱

	EntityId loopPole_[LOOP_POLE_MAX];  // 回転ポール
};
