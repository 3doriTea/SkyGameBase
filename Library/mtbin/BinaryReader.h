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

		using MemoryStreamCore::Read;
	};
}
