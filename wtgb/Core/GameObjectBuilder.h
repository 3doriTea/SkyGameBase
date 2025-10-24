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
		GameObjectBuilder();
		~GameObjectBuilder();

	public:
		template<typename ComponentT>
		ComponentOption<ComponentT>& AddComponent();

	private:
		GameObject* pTarget_;  // 構築するゲームオブジェクト
	};
}

inline wtgb::GameObjectBuilder::GameObjectBuilder()
{
}

inline wtgb::GameObjectBuilder::~GameObjectBuilder()
{
}

#include "GameObjectBuilder.inl"
