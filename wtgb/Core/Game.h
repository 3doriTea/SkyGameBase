#pragma once
#include "pch/pch.h"
#include <Windows.h>
#include "WTGBAssert.h"

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
		static std::string Title();
		/// <summary>
		/// ゲームバージョンを取得する
		/// </summary>
		/// <returns>バージョンの文字列</returns>
		static std::string Version();

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
	pGame_ = new T{};
	pGameLoop_ = new GameLoop{};

	try
	{
		RunProcess();
	}
	catch (const std::exception& e)
	{
		wassert(false && e && "エラー発生");
	}
	catch (int errorCode)
	{
		if (!(false && errorCode && "エラー発生"))
		{
			std::string description
			{
				std::format(
					"{}\r\n\"{}\"より、{}行目の{}関数内でwassertが起動しました。\r\nキャンセルしない場合、例外スローします。Windowsの最終エラーを取得しますか？(はい/いいえ)", "false && errorCode && \"エラー発生\"", "N:\\workhome\\SkyGameBase\\wtgb\\Core\\Game.h", 68, __FUNCTION__)
			};
			std::string title{ wtgb::Game::Title() };
			int result
			{
				MessageBoxW(0, description.c_str(), title.c_str(), 0x00000003L | 0x00000010L | 0x00001000L)
			};

			if (result == 6)
			{
				DWORD errorCode{ GetLastError() };
				MessageBoxW(0, std::format("最終エラーコード:{}", errorCode, title.c_str(), 0x00000000L | 0x00000010L | 0x00001000L); throw "this wassersion error";
			}
			else if (result == 7) {
				throw "this wassersion error";
			}
			else {
				wtgb::Game::Exit();
			}
		};
	}

	delete pGame_;
	pGame_ = nullptr;

	delete pGameLoop_;
	pGameLoop_ = nullptr;

	return 0;
}
