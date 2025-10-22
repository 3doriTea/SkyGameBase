#pragma once
#include "pch/pch.h"
#include "Core/IComponent.h"
#include "Core/Entity.h"

namespace wtgb
{
	constexpr size_t NAME_SIZE{ 16 };
	class GameObjectProperty : public IComponent
	{
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
