#include "pch\pch.h"
#include "InitSequence.h"

wtgb::InitSequence& wtgb::InitSequence::Begin()
{
	return *(new InitSequence{});
}

wtgb::InitSequence::InitSequence() :
	hResult_{}
{
	LOGFW("初期化シーケンスイニット\n");
}

wtgb::InitSequence::~InitSequence()
{
	LOGFW("初期化シーケンスデストロイ\n");
}

wtgb::InitSequence& wtgb::InitSequence::TryRun(const std::function<HRESULT()>& _callback)
{
	if (FAILED(hResult_))
	{
		// 失敗していたらそこで処理をしない
		return *this;
	}

	hResult_ = _callback();

	return *this;
}

HRESULT wtgb::InitSequence::End()
{
	HRESULT hResult{ hResult_ };
	delete this;  // NOTE: 危険？

	return hResult;
}
