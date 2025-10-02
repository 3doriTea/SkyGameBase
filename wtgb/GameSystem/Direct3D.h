#pragma once
#include "Core/IGameSystem.h"

namespace wtgb
{
	class Direct3D : public IGameSystem
	{
	public:
		Direct3D();
		~Direct3D();

		/// <summary>
		/// 更新のタイミング
		/// </summary>
		/// <returns>更新のタイミング</returns>
		const CallType GetCallType() override { return CallType::Frame; }

		/// <summary>
		/// 初期化処理
		/// </summary>
		void Init() override;
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
