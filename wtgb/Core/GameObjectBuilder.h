#pragma once
#include "pch/pch.h"
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
		friend class GameObject;
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

#include "GameObjectBuilder.inl"
