#pragma once
#include "ComponentPool.h"
#include "GameComponent/GameObject.h"

namespace wtgb
{
	class GameObject;

	/// <summary>
	/// コンポーネントプール : ゲームオブジェクト
	/// </summary>
	class CPGameObject : public ComponentPool<std::shared_ptr<GameObject>>
	{
	public:
		CPGameObject();
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
		/// インデックスからエンティティのIdを取得する
		/// </summary>
		/// <param name="_index">インデックス</param>
		/// <returns>エンティティId</returns>
		const EntityId GetEntityId(const size_t _index) const;

		/// <summary>
		/// ゲームオブジェクトを名前から取得する
		/// </summary>
		/// <param name="_name">ゲームオブジェクトの名前</param>
		/// <returns>見つかったゲームオブジェクトのポインタ</returns>
		GameObject* FindGameObject(const std::string_view _name);

		/// <summary>
		/// ゲームオブジェクトをエンティティIdから取得する
		/// </summary>
		/// <param name="_entityId">ゲームオブジェクトのエンティティId</param>
		/// <returns>見つかったゲームオブジェクトのポインタ</returns>
		GameObject* FindGameObject(const EntityId _entityId);

		/// <summary>
		/// 描画処理
		/// </summary>
		void Draw() const;
	};
}
