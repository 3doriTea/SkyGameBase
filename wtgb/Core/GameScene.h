#pragma once
#include "Core/GameSystemViewer.h"
#include "GameSystem/ComponentManager.h"


namespace wtgb
{
	class GameObject;
	class CPGameObject;

	/// <summary>
	/// ゲームシーン
	/// </summary>
	class GameScene
	{
	public:
		/// <summary>
		/// ゲームシーンの設定
		/// </summary>
		struct Config
		{
			inline Config(const ViewerCached _cachedSystem) :
				cachedSystem{ _cachedSystem }
			{
			}
			ViewerCached cachedSystem;
		};

	public:
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
			// NOTE: new するとゲームオブジェクトは自ら自動でプールに追加される
			GameObject* pGameObject{ new T{ _args... } };

			pGameObject->Init();  // 初期化はすぐ呼ぶ

			return entityId;
		}
		virtual ~GameScene() = default;

		GameScene(Config&& _config);

		virtual void Start() {}
		virtual void Update() {}
		virtual void Draw() {}

		ViewerCached System() { return cachedSystem_; }

	private:
		ViewerCached cachedSystem_;  // システム参照用
	};
}
