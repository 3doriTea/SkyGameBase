#pragma once
#include "Common.h"

namespace mtbin
{
	namespace util
	{
		/// <summary>
		/// チャンクIdを比較する
		/// </summary>
		/// <typeparam name="Size">Idのバイト数</typeparam>
		/// <param name="_chunk">チャンクId格納配列</param>
		/// <param name="_str">比較Id文字列</param>
		/// <returns>合致 true / false</returns>
		template<size_t Size>
		inline bool CompareId(const std::array<Byte, Size>& _chunk, const char* _str)
		{
			for (size_t i = 0; i < Size; i++)
			{
				if (_header[i] != _str[i])
				{
					return false;
				}
			}
			return true;
		}
	}
}
