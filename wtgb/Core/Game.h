#pragma once
#include "pch/pch.h"

namespace wtgb
{
	class IGame;
	class GameLoop;
	class GameSystemCollection;

	template<typename T>
	concept GameT = std::is_base_of_v<IGame, T>;

	class Game
	{
	public:
		/// <summary>
		/// ゲームを実行する！
		/// </summary>
		/// <typeparam name="T">IGameを継承した型</typeparam>
		/// <returns>プログラムの終了コード</returns>
		template<GameT T>
		static int Run();

		/// <summary>
		/// ゲームタイトルを取得する
		/// </summary>
		/// <returns>ゲームタイトル文字列</returns>
		static std::string_view Title();
		/// <summary>
		/// ゲームバージョンを取得する
		/// </summary>
		/// <returns>バージョンの文字列</returns>
		static std::string_view Version();

		/// <summary>
		/// ゲームを終了する
		/// </summary>
		static void Exit();

	private:
		/// <summary>
		/// ゲームの実行プロセス
		/// </summary>
		static void RunProcess();

	private:
		static IGame* pGame_;  // ゲームインスタンスのポインタ
		static GameLoop* pGameLoop_;  // ゲームループのポインタ
	};
}

template<wtgb::GameT T>
int wtgb::Game::Run()
{
	T theGame{};
	pGame_ = &theGame;

	try
	{
		RunProcess();
	}
	catch (const std::exception& e)
	{
		throw e;
	}
	catch (int errorCode)
	{
		throw errorCode;
	}

	pGame_ = nullptr;
	return 0;
}
