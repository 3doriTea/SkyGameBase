#pragma once
#include "pch/pch.h"
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameScene;

	class SceneManager : public IGameSystem
	{
	public:
		SceneManager();
		~SceneManager();

		inline const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init(const ViewerInit& _viewer) override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update(const ViewerUpdate& _system) override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

		/// <summary>
		/// シーン遷移する
		/// </summary>
		/// <typeparam name="SceneT">次のシーンの型</typeparam>
		template<typename SceneT>
		inline void Move()
		{
			if (pCurrent_)  // 今のシーンが動いているなら
			{
				RequestClearComponents();  // コンポーネントの破棄依頼をする
			}
			assert(pToNext_ == nullptr && "既に次のシーン遷移が呼ばれている");
			if (pToNext_ == nullptr)
			{
				pToNext_ = new SceneT{};
			}
		}

		/// <summary>
		/// 現在のゲームシーンを取得する
		/// </summary>
		/// <returns>現在のゲームシーンのポインタ</returns>
		inline GameScene* GetCurrentScene() const { return pCurrent_; }

	private:
		void RequestClearComponents();

	private:
		GameScene* pCurrent_;  // 現在のシーン
		GameScene* pToNext_;   // 次に予定されているシーン
		ViewerCached system_;  // システムのキャッシュ
	};
}
