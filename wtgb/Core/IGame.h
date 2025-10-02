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
		virtual std::string GetTitle() const = 0;
		/// <summary>
		/// ゲームのバージョンを取得
		/// </summary>
		/// <returns>ゲームバージョンの取得</returns>
		virtual std::string GetVersion() const = 0;

		virtual void Start(GameSystemCollection* _pGameSystemRegister) = 0;
	};
}
