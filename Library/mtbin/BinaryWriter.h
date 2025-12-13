#pragma once
#include "MemoryStreamCore.h"

namespace mtbin
{
	/// <summary>
	/// バイト配列の読み取り専用とするクラス
	/// </summary>
	class BinaryWriter : public MemoryStreamCore
	{
	public:
		using MemoryStreamCore::MemoryStreamCore;
		BinaryWriter(const MemoryStreamCore& _core);
		~BinaryWriter() {}

		using MemoryStreamCore::Current;
		using MemoryStreamCore::Seek;

		using MemoryStreamCore::Write;
	};
}
