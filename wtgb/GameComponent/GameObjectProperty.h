#pragma once
#include "pch/pch.h"
#include "CommonGameComponent.h"
#include "Core/Entity.h"
#include "GameSystem/CPGameObjectProperty.h"

namespace wtgb
{
	constexpr size_t NAME_SIZE{ 16 };
	const size_t CHILD_COUNT_MAX{ 32 };

	class COMPONENT(GameObjectProperty)
	{
		friend class CPGameObjectProperty;
	public:
		class SETTER(GameObjectProperty)
		{
			SETTER_HEAD(GameObjectProperty)

			Setter& name(const std::string& _name) { GetAccess()->SetName(_name); return *this; }
			SETTER_PARAM(EntityId, parent);
		};

	public:
		GameObjectProperty();
		~GameObjectProperty();

		void Init(ViewerCached _system) override;
		void Update(ViewerCached _system) override {}

		/// <summary>
		/// 名前を取得する
		/// </summary>
		/// <returns>名前</returns>
		std::string_view GetName() const { return { name_ }; }

		/// <summary>
		/// 名前を設定する
		/// </summary>
		/// <param name="_name">新しく設定する名前</param>
		void SetName(const std::string& _name);

		void SetParent(const EntityId _parent);

		const EntityId GetParent() const { return parent_; }

		/// <summary>
		/// ゲームオブジェクトに割り当てられたエンティティIdを取得する
		/// </summary>
		/// <returns>エンティティId</returns>
		const EntityId GetEntityId() const { assert(self_ != INVALID_ENTITY); return self_; }

		void CountChilds() const;

		/// <summary>
		/// 子を追加する
		/// </summary>
		/// <param name="_entityId">子のエンティティId</param>
		void AddChild(const EntityId _entityId);
		/// <summary>
		/// 子を除去する
		/// </summary>
		/// <param name="_entityId">子のエンティティId</param>
		void RemoveChild(const EntityId _entityId);
		/// <summary>
		/// すべての子を除去する
		/// </summary>
		void RemoveAllChild();

	private:
		ViewerCached& System() { return system_; }

	private:
		EntityId self_;         // このゲームオブジェクトのエンティティId
		char name_[NAME_SIZE];  // オブジェクトの名前
		EntityId parent_;       // 親のエンティティId
		int childsCount_;       // 子のエンティティの数
		std::array<EntityId, CHILD_COUNT_MAX> childs_;  // 子のエンティティ数

		ViewerCached system_;
	};
}
