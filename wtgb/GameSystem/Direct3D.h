#pragma once
#include "Core/IGameSystem.h"

#pragma comment(lib, "d3d11.lib")

namespace wtgb
{
	class Direct3DResource;

	/// <summary>
	/// DirectX11-3D系の管理クラス
	/// </summary>
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
		Result Init() override;
		/// <summary>
		/// 更新処理
		/// </summary>
		void Update() override;
		/// <summary>
		/// 終了処理
		/// </summary>
		void End() override;

	private:
		Direct3DResource* pResource_;  // リソースのポインタ
	};
}
