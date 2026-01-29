#pragma once


/// <summary>
/// 表示するUIのインタフェース
/// </summary>
class IVisual
{
public:
	inline IVisual() {}
	inline virtual ~IVisual() {}

	/// <summary>
	/// 表示する
	/// </summary>
	virtual void Show() = 0;
	/// <summary>
	/// 非表示にする
	/// </summary>
	virtual void Hide() = 0;
};
