#pragma once
#include "NumberPlate.h"

class StringPlate : public NumberPlate
{
protected:
	using Moji = int8_t;

	struct Moji_ : NumberPlate::Number_
	{
		enum : Moji
		{
			Dot = NumberPlate::Number_::Max,  // .
			Hiki,    // 匹
			Second,  // 秒
			Minute,  // 分
			Piece,   // 個
		};
	};

public:
	StringPlate(const fs::path& _mojiImageFile);
	~StringPlate();

	void Update() override;

	/// <summary>
	/// 表示する文字列をセットする
	/// </summary>
	/// <param name="_str">表示する文字列</param>
	void SetString(const std::string_view _str) { str_ = _str; }
	/// <summary>
	/// 表示する文字列を取得する
	/// </summary>
	/// <returns>表示する文字列</returns>
	std::string GetString() const { return str_; }

protected:
	/// <summary>
	/// 文字の描画処理
	/// </summary>
	/// <param name="_moji">描画する文字の種類</param>
	void DrawMoji(const Moji _moji);

private:
	inline void SetNumber(const uint32_t _number) override {}
	inline uint32_t GetNumber() const override { return 0; }

protected:
	std::string str_;
};
