#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/GameObjectSetter.h"
#include "Core/IComponent.h"

// TODO: GameObjectは名ばかり、スクリプトコンポーネントだ！

namespace wtgb
{
	class Transform;
	class Property;
	class GameObject;
	class GameObjectBuilder;

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
	class GameObject : public IComponent
	{
	public:
		struct Config;

		class Setter : public GameObjectSetter<GameObject>
		{
		public:
			using GameObjectSetter<GameObject>::GameObjectSetter;
			~Setter();

		};

	public:
		GameObject(std::function<void(GameObjectBuilder&)>);
		virtual ~GameObject() {};

		virtual void Init() {}
		virtual void Update() {}
		virtual void Draw() const {}
		virtual void Release() {}

	protected:
		template<typename ComponentT>
		ComponentT* GetComponent() { return nullptr; }

		template<typename ComponentT>
		ComponentT* AddComponent() { return nullptr; }

		

		Property& Property();
		Transform& Transform();
	private:
		EntityId entityId_;  // エンティティのId

		// TODO: entityIdのみにする
	};
}
