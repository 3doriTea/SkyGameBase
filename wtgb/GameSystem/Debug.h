#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	/// <summary>
	/// デバッグを管理するシステム
	/// </summary>
	class Debug : public IGameSystem
	{
	public:
		Debug();
		~Debug();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
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

	private:
		ModelHandle hSphere_;
	};
}
