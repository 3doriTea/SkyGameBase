#pragma once
#include "pch/pch.h"
#include "Core/Component.h"
#include "Core/ComponentSetter.h"
#include "Core/Entity.h"
#include "GameSystem/CPGameObjectProperty.h"

namespace wtgb
{
	class CPGameObjectProperty;

	constexpr size_t NAME_SIZE{ 16 };
	class GameObjectProperty : public Component<CPGameObjectProperty>
	{
	public:
		class Setter : public ComponentSetter<GameObjectProperty>
		{
		public:
			using ComponentSetter<GameObjectProperty>::ComponentSetter;
			~Setter() {}

			Setter& Name(const std::string& _name) { GetAccess()->SetName(_name); return *this; }
			Setter& Parent(const EntityId _entityId) { GetAccess()->parent_ = _entityId; return *this; }
		};

	public:
		GameObjectProperty();
		~GameObjectProperty();

		void Update() override;

		/// <summary>
		/// 名前を取得する
		/// </summary>
		/// <returns>名前</returns>
		std::string_view GetName() const { return { name_ }; }

		/// <summary>
		/// 名前を設定する
		/// </summary>
		/// <param name="_newName">新しく設定する名前</param>
		void SetName(const std::string& _newName);

		void SetParent(const EntityId _parent);

		const EntityId GetParent() const { return parent_; }

		void CountChilds() const;

	private:
		char name_[NAME_SIZE];  // オブジェクトの名前
		EntityId next_;         // 次の兄弟のエンティティId
		EntityId parent_;       // 親のエンティティId
		EntityId child_;        // 子のエンティティId
	};
}
