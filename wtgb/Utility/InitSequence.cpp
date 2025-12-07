#include "pch\pch.h"
#include "InitSequence.h"

wtgb::InitSequence& wtgb::InitSequence::Begin()
{
	return *(new InitSequence{});
}

wtgb::InitSequence::InitSequence() :
	hResult_{}
{
}

wtgb::InitSequence::~InitSequence()
{
}

wtgb::InitSequence& wtgb::InitSequence::TryRun(const std::function<HRESULT()>& _callback)
{
	if (FAILED(hResult_))
	{
		// ¸”s‚µ‚Ä‚¢‚½‚ç‚»‚±‚Åˆ—‚ğ‚µ‚È‚¢
		return *this;
	}

	hResult_ = _callback();

	return *this;
}

HRESULT wtgb::InitSequence::End()
{
	HRESULT hResult{ hResult_ };
	delete this;  // NOTE: ŠëŒ¯H

	return hResult;
}
