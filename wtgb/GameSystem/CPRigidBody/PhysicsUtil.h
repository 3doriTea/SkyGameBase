#pragma once
#include "CoreType/Vector3.h"

namespace wtgb
{
	class Collider;
	class Transform;

	/// <summary>
	/// 当たり判定セット
	/// </summary>
	struct ColliderSet
	{
		Collider* pCollider;
		Transform* pTransform;
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
		/// <returns>当たっている true / false</returns>
		static bool IsHitFromSection(ColliderSet* _pSelfSection, ColliderSet* _pOther);
		
		/// <summary>
		/// 球から見て当たっているか
		/// </summary>
		/// <param name="_pSelfSphere">球体</param>
		/// <param name="_pOther">相手のコライダー</param>
		/// <returns></returns>
		static bool IsHitFromSphere(ColliderSet* _pSelfSphere, ColliderSet* _pOther);

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
