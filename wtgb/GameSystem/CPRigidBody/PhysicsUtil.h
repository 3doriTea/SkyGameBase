#pragma once
#include "CoreType/Vector3.h"

namespace wtgb
{
	class Collider;
	class Transform;
	class RigidBody;

	/// <summary>
	/// 当たり判定セット
	/// </summary>
	struct ColliderSet
	{
		Collider* pCollider;
		Transform* pTransform;
		RigidBody* pRigidBody;
	};

	/// <summary>
	/// 当たったときの情報
	/// </summary>
	struct CollisionInfo
	{
		bool isHit;        // 当たっているか
		float distance;    // 接点との距離
		Vector3 hitPoint;  // 接点
		Vector3 normal;    // 当たったときの法線
		float depth;       // 埋め込み深さ

		bool isIgnoreFar;            // 遠すぎて除外された
		Vector3 reflectionVelocity;  // 反射ベクトル
		Vector3 push;                // 押し出し
		float time;                  // 当たるまでの時間
	};

	class PhysicsUtil
	{
	public:
		/// <summary>
		/// 当たっているか
		/// </summary>
		/// <param name="_pSelf">自身のコライダー</param>
		/// <param name="_pOther">相手のコライダー</param>
		/// <returns>当たっている true / false</returns>
		static bool IsHit(ColliderSet* _pSelf, ColliderSet* _pOther);

		/// <summary>
		/// セクションから見て当たっているか
		/// </summary>
		/// <param name="_pSelfSection">セクション</param>
		/// <param name="_pOther">相手の当たり判定</param>
		/// <param name="_pCollisionInfo">
		/// <para>当たったときの情報ポインタ渡し</para>
		/// <para>不要な場合はnullptr</para>
		/// </param>
		/// <returns>当たっている true / false</returns>
		static bool IsHitFromSection(ColliderSet* _pSelfSection, ColliderSet* _pOther, CollisionInfo* _pCollisionInfo = nullptr);
		
		/// <summary>
		/// 球から見て当たっているか
		/// </summary>
		/// <param name="_pSelfSphere">球体</param>
		/// <param name="_pOther">相手のコライダー</param>
		/// <param name="_pCollisionInfo">
		/// <para>当たったときの情報ポインタ渡し</para>
		/// <para>不要な場合はnullptr</para>
		/// </param>
		/// <returns></returns>
		static bool IsHitFromSphere(ColliderSet* _pSelfSphere, ColliderSet* _pOther, CollisionInfo* _pCollisionInfo = nullptr);

		/// <summary>
		/// セクションと球が当たっているか
		/// </summary>
		/// <param name="_pSphere">球コライダ</param>
		/// <param name="_pSection">セクションコライダ</param>
		/// <param name="_pCollisionInfo">
		/// <para>当たったときの情報ポインタ渡し</para>
		/// <para>不要な場合はnullptr</para>
		/// </param>
		/// <returns>当たっている true / false</returns>
		static bool IsHitSphereVSSection(ColliderSet* _pSphere, ColliderSet* _pSection, CollisionInfo* _pCollisionInfo = nullptr);

		/// <summary>
		/// 球と球が当たっているか
		/// </summary>
		/// <param name="_pSphereA">球コライダA</param>
		/// <param name="_pSphereB">球コライダB</param>
		/// <param name="_pCollisionInfo">
		/// <para>当たったときの情報ポインタ渡し</para>
		/// <para>不要な場合はnullptr</para>
		/// </param>
		/// <returns>当たっている true / false</returns>
		static bool IsHitSphereVSSphere(ColliderSet* _pSphereA, ColliderSet* _pSphereB, CollisionInfo* _pCollisionInfo = nullptr);

		/// <summary>
		/// 押し出しを取得
		/// </summary>
		/// <param name="_pSelf">自身のコライダー</param>
		/// <param name="_pOther">相手のコライダー</param>
		/// <returns></returns>
		static Vector3 GetPush(ColliderSet* _pSelf, ColliderSet* _pOther);
	private:
		PhysicsUtil() = delete;
		~PhysicsUtil() = delete;
	};
}
