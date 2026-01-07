#pragma once
#include "pch/pch.h"
#include "Core/Entity.h"
#include "Core/GameSystemViewer.h"
#include "GameSystem/ComponentManager.h"
#include "Helper/CommonGameComponent.h"
#include "GameSystem/SceneManager.h"

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

		COMPONENT_HEAD(CPGameObject)
	public:
		struct Config;

		class SETTER(GameObject)
		{
			SETTER_HEAD(GameObject)
		};

	private:
		GameObject();

	public:
		GameObject(const fs::path& _prefab);
		GameObject(std::function<void(GameObjectBuilder&)>);
		virtual ~GameObject();

		virtual void Init() {}
		virtual void Init(ViewerUpdate& _system) {}
		virtual void Update() {}
		virtual void Update(ViewerUpdate& _system) {}
		virtual void Draw() const {}
		virtual void Release() = 0;

		/// <summary>
		/// <para>コンポーネントとしての終了処理</para>
		/// <para>NOTE: 終了処理をオーバーライドする場合はRelease関数を使う</para>
		/// </summary>
		void End() override final;

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

		/// <summary>
		/// ゲームオブジェクトが所属する現在のシーンを取得する
		/// </summary>
		/// <typeparam name="GameSceneT">シーンの型</typeparam>
		/// <returns>シーンの参照</returns>
		template<typename GameSceneT>
		inline GameSceneT& GetScene()
		{
			static_assert(
				std::is_base_of_v<GameScene, GameSceneT>
				&& "指定する型はGameSceneを継承している必要があります。");

			return *(dynamic_cast<GameSceneT*>(System().Get<SceneManager>().GetCurrentScene()));
		}

		/// <summary>
		/// エンティティIdからゲームオブジェクトを探す
		/// </summary>
		/// <param name="_entityId">エンティティId</param>
		/// <returns>見つかったゲームオブジェクトのポインタ / 見つからなければ nullptr</returns>
		GameObject* FindGameObject(const EntityId _entityId);

		/// <summary>
		/// 名前からゲームオブジェクトを探す
		/// </summary>
		/// <param name="_name">名前</param>
		/// <returns>見つかったゲームオブジェクトのポインタ / 見つからなければ nullptr</returns>
		GameObject* FindGameObject(const std::string& _name);

		/// <summary>
		/// 名前から複数のゲームオブジェクトを探す
		/// </summary>
		/// <param name="_name">名前</param>
		/// <param name="_pFoundGameObject">見つかったゲームオブジェクトを格納するポインタ</param>
		bool FindGameObjects(const std::string& _name, std::vector<GameObject*>* _pFoundGameObjects);

		/// <summary>
		/// ゲームオブジェクトプロパティを参照する
		/// </summary>
		/// <returns>ゲームオブジェクトプロパティの参照</returns>
		GameObjectProperty& Property();
		/// <summary>
		/// 座標系コンポーネントを参照する
		/// </summary>
		/// <returns>座標系コンポーネントの参照</returns>
		Transform& Transform();

		/// <summary>
		/// ゲームオブジェクトのエンティティIdを取得する
		/// </summary>
		/// <returns>エンティティId</returns>
		inline EntityId GetEntityId() const { return entityId_; }

	protected:
		ViewerCached& System() const;

	private:
		EntityId entityId_;  // エンティティのId

		// TODO: entityIdのみにする
		bool toDestroy_;  // 削除予定のゲームオブジェクトか true / false

		static ViewerCached* pCachedSystem_;  // cache済みのゲームシステム
	};
}
