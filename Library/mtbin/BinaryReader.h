#pragma once
#include "MemoryStreamCore.h"

namespace mtbin
{
	/// <summary>
	/// バイト配列の書き取り専用とするクラス
	/// </summary>
	class BinaryReader : public MemoryStreamCore
	{
	public:
		using MemoryStreamCore::MemoryStreamCore;
		BinaryReader(const MemoryStreamCore& _core);
		~BinaryReader() {}

		using MemoryStreamCore::Current;
		using MemoryStreamCore::Seek;
		using MemoryStreamCore::Size;

		using MemoryStreamCore::Read;

		/// <summary>
		/// バッファのポインタを取得
		/// </summary>
		/// <returns>読み取り専用のバッファのポインタ</returns>
		inline const mtbin::Byte* Data() { return MemoryStreamCore::Data(); }
	};
}
