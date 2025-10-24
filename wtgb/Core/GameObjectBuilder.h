#pragma once
#include "pch/pch.h"
#include "GameComponent/GameObject.h"
#include "Utility/Accessor.h"
#include "Core/ComponentOption.h"

namespace wtgb
{
	class GameObject;

	class GameObjectBuilder
	{
		template<typename T>
		friend class GameObjectSetter;
		template<typename T>
		friend class ComponentOption;
	public:
		
	private:
		GameObjectBuilder();
		~GameObjectBuilder();

	public:
		template<typename ComponentT>
		ComponentOption<ComponentT>& AddComponent()
		{
			ComponentT* pComponent{ pTarget_->template AddComponent<ComponentT>() };
			return *(new ComponentOption<ComponentT>{ *this, pComponent });
		}

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

//template<typename T, typename ...Args>
//typename wtgb::GameObjectBuilder::template Setter<T>&
//wtgb::GameObjectBuilder::AddComponent(Args... args)
//{
//	T* pComponent{ pTarget_->AddComponent<T>(args...) };
//	GameObjectBuilder::Setter<T>* pSetter
//	{
//		new typename GameObjectBuilder::template Setter<T>{ *this, pComponent }
//	};
//	return *pSetter;
//}

//template<typename T, typename ...Args>
//typename wtgb::GameObjectBuilder::template Setter<T>&
//wtgb::GameObjectBuilder::AddComponent(Args... args)
//{
//	T* pComponent = pTarget_->AddComponent<T>(args...);
//	auto* pSetter = new typename wtgb::GameObjectBuilder::template Setter<T>{ *this, pComponent };
//	return *pSetter;
//}
