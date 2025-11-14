#pragma once
#include "ComponentPool.h"
#include "GameComponent/GameObjectProperty.h"

namespace wtgb
{
	class GameObjectProperty;

	class CPGameObjectProperty : public ComponentPool<GameObjectProperty>
	{
	public:
		CPGameObjectProperty();
		~CPGameObjectProperty();

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;

		/// <summary>
		/// 親子関係をセットする
		/// </summary>
		/// <param name="_parent">親のエンティティId</param>
		/// <param name="_child">子のエンティティId</param>
		void SetFamily(const EntityId _parent, const EntityId _child);

		const EntityId GetEntityId(const GameObjectProperty* _p) const;
	};
}
