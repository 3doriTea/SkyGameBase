#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class ImGuiSystem : public IGameSystem
	{
	public:
		ImGuiSystem();
		~ImGuiSystem();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Cycle; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		/// <param name="_system">システムアクセス</param>
		/// <returns>結果</returns>
		Result Init(const ViewerInit& _system) override;

		/// <summary>
		/// 更新処理
		/// </summary>
		/// <param name="_system">システムアクセス</param>
		void Update(const ViewerUpdate& _system) override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		bool firstFrame_;
	};
}
