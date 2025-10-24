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

		const CallType GetCallType() override { return CallType::Frame; }

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

		template<typename SceneT>
		void Move()
		{
			assert(pToNext_ == nullptr && "既に次のシーン遷移が呼ばれている");
			if (pToNext_ == nullptr)
			{
				pToNext_ = new SceneT{};
			}
		}

	private:
		GameScene* pCurrent_;  // 現在のシーン
		GameScene* pToNext_;   // 次に予定されているシーン
	};
}
