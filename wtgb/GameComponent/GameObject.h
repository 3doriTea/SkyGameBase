#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/GameSystemViewer.h"
#include "GameSystem/ComponentManager.h"
#include "CommonGameComponent.h"
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

	/// <summary>
	/// <para>ゲームオブジェクト (中身はエンティティIdのみ)</para>
	/// <para>軽量なため本体は基本的にコピーして利用</para>
	/// <para>オリジナルゲームオブジェクトはこれを派生し、参照を利用</para>
	/// </summary>
	class COMPONENT(GameObject)
	{
		template<typename ComponentT>
		friend class ComponentSetter;

		friend class CPGameObject;
	public:
		struct Config;

		class SETTER(GameObject)
		{
			SETTER_HEAD(GameObject)
		};

	private:
		GameObject();

	public:
		GameObject(std::function<void(GameObjectBuilder&)>);
		virtual ~GameObject();

		virtual void Init() {}
		virtual void Init(ViewerUpdate& _system) {}
		virtual void Update() = 0;
		virtual void Update(ViewerUpdate& _system) {}
		virtual void Draw() const {}
		virtual void Release() {}

		/// <summary>
		/// このゲームオブジェクトを削除する
		/// </summary>
		void DestroyMe() { toDestroy_ = true; }
		/// <summary>
		/// このゲームオブジェクトは削除予定か
		/// </summary>
		/// <returns>削除予定である true / false</returns>
		bool IsToDestroy() const { return toDestroy_; }

		template<typename ComponentT>
		ComponentT& GetComponent() { return System().Get<ComponentManager>().Get<ComponentT>(entityId_); }

		template<typename ComponentT>
		ComponentT& AddComponent() { return System().Get<ComponentManager>().Add<ComponentT>(entityId_); }

		GameObjectProperty& Property();
		Transform& Transform();

	protected:
		ViewerCached& System() const;

	private:
		EntityId entityId_;  // エンティティのId

		bool toDestroy_;  // 削除予定のゲームオブジェクトか true / false

		// TODO: entityIdのみにする
		static ViewerCached* pCachedSystem_;  // cache済みのゲームシステム
	};
}
