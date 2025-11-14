#pragma once
#include "Core/GameSystemCollection.h"
#include "Core/GameSystemViewer.h"
#include "GameSystem/ComponentManager.h"
#include "GameSystem/CPGameObject.h"

namespace wtgb
{
	class GameObject;
	class CPGameObject;

	/// <summary>
	/// ゲームシーン
	/// </summary>
	class GameScene
	{
		friend class SceneManager;
	public:
		struct Config
		{
			
		};

	public:
		GameScene(Config&& _config);
		virtual ~GameScene();

		virtual void Start() {}
		virtual void Update() {}
		virtual void Draw() {}

	protected:
		/// <summary>
		/// ゲームオブジェクトをインスタンスする
		/// </summary>
		/// <typeparam name="T">ゲームオブジェクトの型</typeparam>
		/// <typeparam name="...Args">可変長引数型</typeparam>
		/// <param name="..._args">可変長引数</param>
		/// <returns>インスタンスされたゲームオブジェクトの ptr / nullptr</returns>
		template<typename T, typename ...Args>
		EntityId Instantiate(Args... _args)
		{
			EntityId entityId{ cachedSystem_.Get<ComponentManager>().GenerateEntity() };

			GameObject* pGameObject
			{
				cachedSystem_.Get<CPGameObject>().Add(
					entityId,
					new T{ _args... })
			};

			pGameObject->Init();  // 初期化はすぐ呼ぶ

			return entityId;
		}

		ViewerCached System() { return cachedSystem_; }

	private:
		static ViewerCached cachedSystem_;
	};
}
