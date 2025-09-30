#pragma once
#include "IGame.h"

namespace wtgb
{
	template<typename T>
	concept GameT = std::is_base_of_v<IGame, T>;

	/// <summary>
	/// ゲームを実行する！
	/// </summary>
	/// <typeparam name="T">IGameを継承した型</typeparam>
	/// <returns>プログラムの終了コード</returns>
	template<GameT T>
	int Run();
}

template<wtgb::GameT T>
int wtgb::Run()
{
	return 0;
}
