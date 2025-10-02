#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class GameWindow : public IGameSystem
	{
	public:
		GameWindow();
		~GameWindow();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Cycle; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		Result Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;
	};
}
