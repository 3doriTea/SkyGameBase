#pragma once
#include "Common.h"

namespace mtbin
{
	namespace util
	{
		/// <summary>
		/// ƒ`ƒƒƒ“ƒNId‚ğ”äŠr‚·‚é
		/// </summary>
		/// <typeparam name="Size">Id‚ÌƒoƒCƒg”</typeparam>
		/// <param name="_chunk">ƒ`ƒƒƒ“ƒNIdŠi”[”z—ñ</param>
		/// <param name="_str">”äŠrId•¶š—ñ</param>
		/// <returns>‡’v true / false</returns>
		template<size_t Size>
		inline bool CompareId(const std::array<Byte, Size>& _chunk, const char* _str)
		{
			for (size_t i = 0; i < Size; i++)
			{
				if (_chunk[i] != _str[i])
				{
					return false;
				}
			}
			return true;
		}

		template<size_t Size>
		inline void Reverse(std::array<Byte, Size>& _ref)
		{
			std::reverse(_ref.begin(), _ref.end());
		}
	}
}
