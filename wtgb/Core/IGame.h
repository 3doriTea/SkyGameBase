#pragma once
//#include <>

namespace wtgb
{
	/// <summary>
	/// ゲーム本体のインタフェース
	/// </summary>
	class IGame
	{
	protected:
		void GetTitle();
	private:
		IGame() = default;
		virtual ~IGame() = default;
	};
}
