#pragma once
#include "pch/pch.h"
#include "Utility/Accessor.h"
#include "Core/ComponentOption.h"

namespace wtgb
{
	class GameObject;

	class GameObjectBuilder
	{
		template<typename T>
		friend class ComponentSetter;
		template<typename T>
		friend class ComponentOption;
	public:
		
	private:
		GameObjectBuilder(GameObject& _target);
		~GameObjectBuilder();

	public:
		template<typename ComponentT>
		ComponentOption<ComponentT>& AddComponent();

		GameObjectBuilder& Build()
		{
			return *this;
		}

	private:
		GameObject& target_;  // 構築するゲームオブジェクト
	};
}

inline wtgb::GameObjectBuilder::GameObjectBuilder(GameObject& _target) :
	target_{ _target }
{
}

inline wtgb::GameObjectBuilder::~GameObjectBuilder()
{
}

#include "GameObjectBuilder.inl"
