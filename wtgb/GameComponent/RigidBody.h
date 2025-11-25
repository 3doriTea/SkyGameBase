#pragma once
#include "CommonGameComponent.h"
#include "GameSystem/CPRigidBody.h"

namespace wtgb
{
	class COMPONENT(RigidBody)
	{
		friend class CPRigidBody;
	public:
		class SETTER(RigidBody)
		{
			SETTER_HEAD(RigidBody)

			SETTER_PARAM(Vector3, velocity)
			SETTER_PARAM(float, drag)
			SETTER_PARAM(Vector3, angularVelocity)
			SETTER_PARAM(float, angularDrag)
			SETTER_PARAM(bool, useSphereCollider)
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

	private:
		Vector3 velocity_;  // 向きを持った速度 (m/s)
		float drag_;      // 抗力
		
		Vector3 angularVelocity_;  // 回転速度 (r/s)
		float angularDrag_;      // 回転抗力

		bool useSphereCollider_;  // 球の当たり判定を使うか
		bool useGravity_;  // 重力がかかるかどうか

	};
}
