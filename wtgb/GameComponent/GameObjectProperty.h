#pragma once
#include "pch/pch.h"
#include "Helper/CommonGameComponent.h"
#include "Core/Entity.h"

namespace wtgb
{
	static constexpr size_t NAME_SIZE{ 16 };
	static const size_t CHILD_COUNT_MAX{ 1024 };

	class COMPONENT(GameObjectProperty)
	{
		COMPONENT_HEAD(GameObjectProperty)

		class SETTER(GameObjectProperty)
		{
			SETTER_HEAD(GameObjectProperty)

			Setter& name(const std::string& _name) { GetAccess()->SetName(_name); return *this; }
			SETTER_PARAM(EntityId, parent)
		};

	public:
		GameObjectProperty();
		~GameObjectProperty();

		void Init(ViewerCached _system) override;
		void Update(ViewerCached _system) override;

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

		/// <summary>
		/// 親エンティティを設定する
		/// </summary>
		/// <param name="_parent"></param>
		void SetParent(const EntityId _parent);

		const EntityId GetParent() const { return parent_; }

		/// <summary>
		/// ゲームオブジェクトに割り当てられたエンティティIdを取得する
		/// </summary>
		/// <returns>エンティティId</returns>
		const EntityId GetEntityId();

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

		const std::array<EntityId, CHILD_COUNT_MAX>& GetChilds() const { return childs_; }

	private:
		const ViewerCached& System() const { return system_; }

	private:
		EntityId self_;         // このゲームオブジェクトのエンティティId
		char name_[NAME_SIZE];  // オブジェクトの名前
		EntityId parent_;       // 親のエンティティId
		int childsCount_;       // 子のエンティティの数
		std::array<EntityId, CHILD_COUNT_MAX> childs_;  // 子のエンティティ数

		ViewerCached system_;
	};
}
