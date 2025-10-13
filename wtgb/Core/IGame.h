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
		IGame() = default;
		virtual ~IGame() = default;

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

		virtual void StartRegister(const GameSystemCollection::GameSystemAdder& _pGameSystemAdder) = 0;
		virtual void StartSetup(const GameSystemCollection::GameSystemViewer& _pGameSystemsViewer) = 0;
	};
}
