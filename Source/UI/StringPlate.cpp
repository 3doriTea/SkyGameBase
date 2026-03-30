#include "StringPlate.h"

StringPlate::StringPlate(const fs::path& _mojiImageFile) :
	NumberPlate{ _mojiImageFile.string() }
{
}

StringPlate::~StringPlate()
{
}

void StringPlate::Update()
{
	currDrawPos_ = beginDrawPos_;

	for (char c : str_)
	{
		if ('0' <= c && c <= '9')
		{
			Number num{ c - '0' };
			DrawNumber(num);
		}
		else if ('.' == c)
		{
			DrawMoji(Moji_::Dot);
		}
		else if ('p' == c)
		{
			DrawMoji(Moji_::Piece);
		}
		else if ('s' == c)
		{
			DrawMoji(Moji_::Second);
		}
		else if ('m' == c)
		{
			DrawMoji(Moji_::Minute);
		}
		else if ('h' == c)
		{
			DrawMoji(Moji_::Hiki);
		}
		else
		{
			wassert(false && "指定できない文字");
		}
	}
}

void StringPlate::DrawMoji(const Moji _moji)
{
	// NOTE: 単なるインデクスを渡すだけでいい
	DrawNumber(static_cast<int8_t>(_moji));
}
