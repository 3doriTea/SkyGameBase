#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/ComponentSetter.h"
#include "Core/Component.h"
#include "Core/GameSystemViewer.h"
#include "GameSystem/ComponentManager.h"
#include "GameSystem/CPGameObject.h"

// TODO: GameObjectは名ばかり、スクリプトコンポーネントだ！

namespace wtgb
{
	class Transform;
	class GameObjectProperty;
	class GameObject;
	class GameObjectBuilder;

	/// <summary>
	/// ゲームオブジェクトを継承している型
	/// </summary>
	template<typename T>
	concept GameObjectT = std::is_base_of_v<GameObject, T>;

	class CPGameObject;

	/// <summary>
	/// <para>ゲームオブジェクト (中身はエンティティIdのみ)</para>
	/// <para>軽量なため本体は基本的にコピーして利用</para>
	/// <para>オリジナルゲームオブジェクトはこれを派生し、参照を利用</para>
	/// </summary>
	class GameObject : public Component<CPGameObject>
	{
		friend class GameScene;
	public:
		struct Config;

		class Setter : public ComponentSetter<GameObject>
		{
		public:
			using ComponentSetter<GameObject>::ComponentSetter;
			~Setter();

		};

	private:
		GameObject();

	public:
		GameObject(std::function<void(GameObjectBuilder&)>);
		virtual ~GameObject() {};

		virtual void Init() {}
		virtual void Init(ViewerUpdate& _system) {}
		virtual void Update() {}
		virtual void Update(ViewerUpdate& _system) {}
		virtual void Draw() const {}
		virtual void Release() {}

		template<typename ComponentT>
		ComponentT* GetComponent() { return System().Get<ComponentManager>().Get<ComponentT>(entityId_); }

		template<typename ComponentT>
		ComponentT* AddComponent() { return System().Get<ComponentManager>().Add<ComponentT>(entityId_); }

		GameObjectProperty& Property();
		Transform& Transform();

	protected:
		ViewerCached& System() const;

	private:
		EntityId entityId_;  // エンティティのId

		// TODO: entityIdのみにする
		ViewerCached* pCachedSystem_;  // cache済みのゲームシステム
	};
}
