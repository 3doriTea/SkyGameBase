#pragma once
#include "pch/pch.h"

namespace
{
	// キーボードのステートの要素数
	const size_t KEY_BOARD_STATE_SIZE{ 256 };
}

namespace wtgb
{
	/// <summary>
	/// 入力データキャリア
	/// </summary>
	class InputData
	{
		friend class Input;
	public:
		using KeyBoardStateArray = std::array<BYTE, KEY_BOARD_STATE_SIZE>;

	private:
		InputData() :
			keyBoardState_{},
			keyBoardStatePrev_{},
			mousePosition_{},
			mousePositionPrev_{},
			mouseState_{},
			mouseStatePrev_{}
		{}
		~InputData() {}

	private:
		// 現在のキーボード状態
		KeyBoardStateArray keyBoardState_;
		// 前回のキーボード状態
		KeyBoardStateArray keyBoardStatePrev_;
		// 現在のマウス座標
		Vector2Int mousePosition_;
		// 前回のマウス座標
		Vector2Int mousePositionPrev_;
		// 現在のマウス状態
		DIMOUSESTATE mouseState_;
		// 前回のマウス状態
		DIMOUSESTATE mouseStatePrev_;
	};
}
