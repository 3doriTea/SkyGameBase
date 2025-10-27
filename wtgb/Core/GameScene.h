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
		GameObject* Instantiate(Args... _args)
		{
			if (pCachedSystem_)
			{
				EntityId entityId{ pCachedSystem_->Get<ComponentManager>().AddEntity() };

				return &pCachedSystem_->Get<CPGameObject>().Add(entityId);
			}

			return nullptr;
		}

	private:
		ViewerCached* pCachedSystem_;
	};
}
