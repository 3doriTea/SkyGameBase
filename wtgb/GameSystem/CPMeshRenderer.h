#pragma once
#include "ComponentPool.h"
#include "GameComponent/MeshRenderer.h"

namespace wtgb
{
	/// <summary>
	/// コンポーネントプール : メッシュ描画
	/// </summary>
	class CPMeshRenderer : public ComponentPool<MeshRenderer>
	{
	public:
		CPMeshRenderer();
		~CPMeshRenderer();

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
