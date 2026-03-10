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

		/// <summary>
		/// 座標系のローカル要素だけ計算をする
		/// </summary>
		/// <param name="_pTransform">計算する座標系のポインタ</param>
		void CalculateLocalTransform(Transform* _pTransform);

		/// <summary>
		/// 親がいない座標系の計算をする
		/// </summary>
		/// <param name="_pRoot">計算する座標系のポインタ</param>
		void CalculateTransformRoot(Transform* _pRoot);
	};
}
