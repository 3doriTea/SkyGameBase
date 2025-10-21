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

		template <typename CurrAryT, typename PrevAryT, typename CodeT>
		inline static Checker<CodeT> GenIsUp(const CurrAryT& _currArray, const PrevAryT& _prevArray)
		{
			return [&_currArray, &_prevArray](const CodeT _code)
				{
					return Check::IsUp
						(_currArray[static_cast<int>(_keyCode)])
						(_prevArray[static_cast<int>(_keyCode)]);
				};
		}

		template <typename CurrAryT, typename PrevAryT, typename CodeT>
		inline static Checker<CodeT> GenIsDown(const CurrAryT& _currArray, const PrevAryT& _prevArray)
		{
			return [&_currArray, &_prevArray](const CodeT _code)
				{
					return Check::IsDown
					(_currArray[static_cast<int>(_keyCode)])
						(_prevArray[static_cast<int>(_keyCode)]);
				};
		}
	};
}
