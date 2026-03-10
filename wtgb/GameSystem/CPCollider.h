#pragma once
#include "ComponentPool.h"
#include "GameComponent/Collider.h"

namespace wtgb
{
	class Collider;

	/// <summary>
	/// コンポーネントプール : 当たり判定(Collider)
	/// </summary>
	class CPCollider : public ComponentPool<Collider>
	{
	public:
		CPCollider() {}
		~CPCollider() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override {}
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
	};
}
