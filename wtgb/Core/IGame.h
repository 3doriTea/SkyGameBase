#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// ゲーム本体のインタフェース
	/// </summary>
	class IGame
	{
	protected:
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

		virtual void Start() = 0;
	private:
		IGame() = default;
		virtual ~IGame() = default;
	};
}
