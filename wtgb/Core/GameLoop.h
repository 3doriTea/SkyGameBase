#pragma once

namespace wtgb
{
	class GameSystemCollection;

	/// <summary>
	/// ゲームループを実行するクラス
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
	};
}
