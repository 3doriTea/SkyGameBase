#pragma once

namespace wtgb
{
	/// <summary>
	/// ゲームループ
	/// </summary>
	class GameLoop
	{
	public:
		/// <summary>
		/// ループ実行
		/// </summary>
		void RunLoop();

	private:
		bool isRunning_;  // ゲームループ実行中 true / false
		float deltaTime_;  // フレーム間時間
	};
}
