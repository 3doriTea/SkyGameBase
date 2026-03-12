#pragma once
#include <wtgb.h>

/// <summary>
/// リフト構造物
/// </summary>
class LiftStructure : public GameObject
{
	enum struct LoopPoleType
	{
		Uppper,  // 頂上のポール
		Middle,  // 中間のポール
		Lower,   // 麓のポール
	};

	/// <summary>
	/// リフトの中間ポール情報
	/// </summary>
	struct LiftPole
	{
		inline LiftPole(const Vector3& _position, const EntityId _entity) :
			position{ _position },
			entity{ _entity }
		{ }
		Vector3 position;  // ポールの座標
		EntityId entity;   // ポールのエンティティ

		/// <summary>
		/// 座椅子が通過するポールの座標を取得する
		/// </summary>
		/// <param name="_height">座椅子が通過する高さ</param>
		/// <returns>座椅子が通過する座標</returns>
		inline Vector3 GetChairPositionAndRotateY(const float _height)
		{
			return position + (Vector3::Up() * _height);
		}
	};
public:
	LiftStructure(const EntityId _stage, const float _polePosX);
	~LiftStructure();

	void Init() override;
	void Update() override;
	void Release() override;


	/// <summary>
	/// ポールを生成
	/// </summary>
	void GeneratePoles();

	/// <summary>
	/// 椅子を生成
	/// </summary>
	void GenerateChairs();

	/// <summary>
	/// 座椅子の座標を取得する
	/// </summary>
	/// <param name="_length">どの長さ付近か</param>
	/// <returns>(座椅子の座標 xyz込み, 回転y軸)</returns>
	std::tuple<Vector3, float> GetChairPositionAndRotateY(const float _length);

	/// <summary>
	/// ロープの高さを取得する
	/// </summary>
	/// <param name="_z"></param>
	/// <returns>ロープの高さ</returns>
	float GetRopeHeight(const float _z);

	float GetRotationSpeedPerSec() const { return (DirectX::XM_2PI / 360.0f) * 30.0f; }

private:
	void OnLoad(const json& _json);

private:
	float ropeSpasing_;  // ロープの幅
	int chairsCount_;    // 座椅子プールに用意する椅子の数
	float poleDistance_;  // ポールどうしの距離
	float ropeHeight_;    // ポールの地面からラインまでの高さ

	float polePosX_;      // ポールを設置するx座標
	EntityId stage_;  // ステージ

	std::vector<LiftPole> poles_;   // 中間ポールたち
	std::vector<EntityId> chairs_;  // 椅子
	float totalLength_;             // ロープの全長
	float laneLength_;              // 直線部分1本の長さ
	float curveLength_;             // 端の半円の長さ
};
