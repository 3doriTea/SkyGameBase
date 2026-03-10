#pragma once
#include "pch/pch.h"

namespace wtgb
{
	class InputChecker
	{
		template<typename CodeT>
		using Checker = std::function<bool(const CodeT _code)>;
		
		InputChecker() = delete;
		~InputChecker() = delete;

		friend class Input;
		
		// TODO: このTが真偽値にキャストできることをコンセプトにする
		template <typename T>
		inline static std::function<bool(const T _previous)> IsDown(const T _current)
		{
			return [_current](const T _previous)
				{
					return _current  // 今がON
						&&           // かつ
						!_previous;  // 前がOFF
					// -> 押された瞬間！
				};
		}

		// TODO: このTが真偽値にキャストできることをコンセプトにする
		template <typename T>
		inline static std::function<bool(const T _previous)> IsUp(const T _current)
		{
			return [_current](const T _previous)
				{
					return !_current  // 今がON
						&&            // かつ
						_previous;    // 前がOFF
					// -> 押された瞬間！
				};
		}

		template <typename StateArrayT, typename CodeT>
		inline static Checker<CodeT> GenIsUp(const StateArrayT& _currArray, const StateArrayT& _prevArray)
		{
			return [&_currArray, &_prevArray](const CodeT _code)
				{
					return IsUp(_currArray[static_cast<int>(_code)])
						(_prevArray[static_cast<int>(_code)]);
				};
		}

		template <typename StateArrayT, typename CodeT>
		inline static Checker<CodeT> GenIsDown(const StateArrayT& _currArray, const StateArrayT& _prevArray)
		{
			return [&_currArray, &_prevArray](const CodeT _code)
				{
					return IsDown(_currArray[static_cast<int>(_code)])
						(_prevArray[static_cast<int>(_code)]);
				};
		}

		template <typename StateArrayT, typename CodeT>
		inline static Checker<CodeT> GenIsPress(const StateArrayT& _currArray)
		{
			return [&_currArray](const CodeT _code)
				{
					return _currArray[static_cast<int>(_code)];
				};
		}
	};
}
