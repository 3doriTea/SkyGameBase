#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPRigidBody.h"

namespace
{
	const size_t HIT_COLLIDER_BUFFER_SIZE{ 10 };
}

namespace wtgb
{
	class Collider;

	class COMPONENT(RigidBody)
	{
		friend class CPRigidBody;
	public:
		class SETTER(RigidBody)
		{
			SETTER_HEAD(RigidBody)

			SETTER_PARAM(float, mass)
			SETTER_PARAM(Vector3, velocity)
			SETTER_PARAM(float, drag)
			SETTER_PARAM(float, bounciness)
			SETTER_PARAM(Vector3, angularVelocity)
			SETTER_PARAM(float, angularDrag)
			SETTER_PARAM(bool, useGravity)
		};

	public:
		RigidBody();
		~RigidBody() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init(ViewerCached _system) override {}
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// 何かしらに当たっているコライダ数
		/// </summary>
		/// <returns></returns>
		inline int GetHitCount() const { return static_cast<int>(onHitCollidersCount_); }
		/// <summary>
		/// 何かしらに当たっているか
		/// </summary>
		/// <returns>当たっている true / false</returns>
		inline bool IsHit() const { return GetHitCount() > 0; }

		/// <summary>
		/// 当たっている全コライダを取得する
		/// </summary>
		/// <param name="_pHitColliderVector">当たっているコライダ格納用vectorのポインタ渡し</param>
		void GetHitColliders(std::vector<Collider*>* _pHitColliderVector);

		/// <summary>
		/// 速度を加える
		/// </summary>
		/// <param name="_addV">ワールド座標系での速度</param>
		inline void AddVelocity(const Vector3& _addV) { velocity_ = velocity_ + _addV; }
		/// <summary>
		/// 回転速度を加える
		/// </summary>
		/// <param name="_addT">ワールド座標系での速度</param>
		inline void AddTorque(const Vector3& _addT) { angularVelocity_ = angularVelocity_ + _addT; }

	private:
		/// <summary>
		/// 当たっているコライダを追加する
		/// </summary>
		void AddHitCollider(Collider* _pCollider);
		/// <summary>
		/// 当たっているコライダを全てクリアする
		/// </summary>
		void ClearHitCollider();

	private:
		float mass_;  // 質量 (kg)

		Vector3 velocity_;  // 向きを持った速度 (m/s)
		float drag_;      // 抗力
		
		Vector3 angularVelocity_;  // 回転速度 (r/s)
		float angularDrag_;      // 回転抗力

		bool useSphereCollider_;  // 球の当たり判定を使うか
		bool useGravity_;  // 重力がかかるかどうか

		// MEMO: e = 1     : 完全弾性衝突 ﾊﾞﾝ
		//     : 0 < e < 1 : 弾性 ﾎﾞｲﾝ
		//     : e = 0     : 完全非弾性 ﾍﾟﾀｯ
		float bounciness_;  // 反発係数 = e

		Vector3 push_;  // 内部計算用押し出し

		size_t onHitCollidersCount_;  // 当たっているコライダ数
		// 当たっているコライダ一覧
		std::array<Collider*, HIT_COLLIDER_BUFFER_SIZE> onHitColliders_;

		Vector3 prevPosition_;  // 前回計算時のワールド座標
	};
}
