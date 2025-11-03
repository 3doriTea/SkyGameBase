#pragma once
#include "ComponentPool.h"
#include "GameComponent/ModelMesh.h"

namespace wtgb
{
	class ModelMesh;
	/// <summary>
	/// コンポーネントプール : モデルメッシュ
	/// </summary>
	class CPModelMesh : public ComponentPool<ModelMesh>
	{
	public:
		CPModelMesh();
		~CPModelMesh();

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
