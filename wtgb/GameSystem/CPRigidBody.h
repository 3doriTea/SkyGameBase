#pragma once
#include "ComponentPool.h"
#include "GameComponent/RigidBody.h"

namespace wtgb
{
	class RigidBody;

	/// <summary>
	/// コンポーネントプール : 剛体(RigidBody)
	/// </summary>
	class CPRigidBody : public ComponentPool<RigidBody>
	{
	public:
		CPRigidBody();
		~CPRigidBody();

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
	};
}
