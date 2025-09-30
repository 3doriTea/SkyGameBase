#pragma once

namespace wtgb
{
	/// <summary>
	/// ゲームシステム
	/// </summary>
	class IGameSystem
	{
	public:
		IGameSystem() {}
		virtual ~IGameSystem() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		virtual void Init() = 0;
		/// <summary>
		/// 更新処理
		/// </summary>
		virtual void Update() = 0;
	};
}
