#pragma once
#include "ComponentPool.h"
#include "GameComponent/GameObject.h"

namespace wtgb
{
	class GameObject;

	/// <summary>
	/// コンポーネントプール : ゲームオブジェクト
	/// </summary>
	class CPGameObject : public ComponentPool<GameObject*>
	{
	public:
		CPGameObject();
	private:
		~CPGameObject();

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	public:
		/// <summary>
		/// 描画処理
		/// </summary>
		void Draw() const;
	};
}
