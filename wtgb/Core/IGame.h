#pragma once
#include "pch/pch.h"
#include "GameSystemCollection.h"


namespace wtgb
{
	/// <summary>
	/// ゲーム本体のインタフェース
	/// </summary>
	class IGame
	{
		friend class Game;  // ゲームクラスからは private操作可能

	protected:
		inline IGame() {};
		inline virtual ~IGame() {};

		/// <summary>
		/// ゲームのタイトルを取得
		/// </summary>
		/// <returns>ゲームのタイトル文字列</returns>
		virtual const char* GetTitle() const = 0;
		/// <summary>
		/// ゲームのバージョンを取得
		/// </summary>
		/// <returns>ゲームバージョンの取得</returns>
		virtual const char* GetVersion() const = 0;

		/// <summary>
		/// 登録開始処理
		/// </summary>
		/// <param name="_pGameSystemAdder">システムを登録してもらう</param>
		virtual void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) = 0;
	};
}
