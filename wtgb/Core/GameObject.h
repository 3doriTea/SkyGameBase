#pragma once
#include "pch/pch.h"
#include "Entity.h"
#include "GameObjectBuilder.h"

namespace wtgb
{
	class Transform;
	class Property;
	class GameObject;

	/// <summary>
	/// ゲームオブジェクトを継承している型
	/// </summary>
	template<typename T>
	concept GameObjectT = std::is_base_of_v<GameObject, T>;

	/// <summary>
	/// <para>ゲームオブジェクト (中身はエンティティIdのみ)</para>
	/// <para>軽量なため本体は基本的にコピーして利用</para>
	/// <para>オリジナルゲームオブジェクトはこれを派生し、参照を利用</para>
	/// </summary>
	class GameObject
	{
	public:
		struct Config;

	public:
		GameObject(std::function<void(GameObjectBuilder&)>);
		virtual ~GameObject() {};

		virtual void Init() {}
		virtual void Update() {}
		virtual void Draw() const {}
		virtual void Release() {}

	protected:
		template<typename ComponentT>
		ComponentT* GetComponent();

		template<typename ComponentT>
		ComponentT* AddComponent();

		

		Property& Property();
		Transform& Transform();
	private:
		EntityId entityId_;  // エンティティのId
	};
}
