#pragma once

namespace wtgb
{
	template<typename T>
	inline void SafeDelete(T*& _p)
	{
		// 指定の型が不完全型ではないなら問題ないよね!!
		using Ary = char[sizeof(T) ? 1 : -1];
		(void)sizeof(Ary);

		if (_p)
		{
			delete _p;
			_p = nullptr;
		}
	}

	template<typename T>
	inline void SafeRelease(T*& _p)
	{
		// 指定の型が不完全型ではないなら問題ないよね!!
		using Ary = char[sizeof(T) ? 1 : -1];
		(void)sizeof(Ary);

		if (_p)
		{
			_p->Release();
			_p = nullptr;
		}
	}
}

#define SAFE_DELETE(p)\
wtgb::SafeDelete(p);

#define SAFE_RELEASE(p)\
wtgb::SafeRelease(p);
