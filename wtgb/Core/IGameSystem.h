#pragma once
#include "pch/pch.h"
#include "GameSystemCollection.h"

namespace wtgb
{
	class GameSystemCollection;
	class GameSystemCollection::GameSystemViewer;
	/// <summary>
	/// ゲームシステム
	/// </summary>
	class IGameSystem
	{
	public:
		using Viewer = GameSystemCollection::GameSystemViewer;

		/// <summary>
		/// 呼び出しタイミングの種類
		/// </summary>
		enum struct CallType
		{
			Cycle,  // ゲームループサイクル
			Frame,  // 描画フレーム
		};
	public:
		IGameSystem() {}
		virtual ~IGameSystem() {}

		/// <summary>
		/// 呼び出しタイミングの種類を取得する
		/// </summary>
		/// <returns>呼び出しタイミングの種類</returns>
		virtual const CallType GetCallType() = 0;
		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual Result Init(const Viewer& _viewer) = 0;
		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;
		/// <summary>
		/// 終了処理
		/// </summary>
		virtual void End() = 0;

	protected:
		//void 
	};
}
