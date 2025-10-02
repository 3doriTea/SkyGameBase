#pragma once

namespace wtgb
{
	class GameSystemCollection;

	/// <summary>
	/// ゲームループ
	/// </summary>
	class GameLoop
	{
	public:
		GameLoop();
		~GameLoop();

		/// <summary>
		/// ループ実行
		/// </summary>
		Result RunLoop(GameSystemCollection* _pGameSystemRegister);

		/// <summary>
		/// ループを止める
		/// </summary>
		void Stop();

	private:
		bool isRunning_;  // ゲームループ実行中 true / false
		float deltaTime_;  // フレーム間時間
	};
}
