#pragma once
#include "MemoryStreamCore.h"

namespace mtbin
{
	/// <summary>
	/// バイト配列の読み書きするクラス
	/// </summary>
	class MemoryStream : public MemoryStreamCore
	{
	public:
		using MemoryStreamCore::MemoryStreamCore;
		~MemoryStream() {}

		using MemoryStreamCore::Current;
		using MemoryStreamCore::Seek;

		using MemoryStreamCore::Read;
		using MemoryStreamCore::Write;
	};
}
