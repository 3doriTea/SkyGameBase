#pragma once
#include "ComponentPool.h"
#include "GameComponent/Transform.h"

namespace wtgb
{
	class Transform;
	/// <summary>
	/// コンポーネントプール : 座標変換(Transform)
	/// </summary>
	class CPTransform : public ComponentPool<Transform>
	{
	public:
		CPTransform();
		~CPTransform();

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
