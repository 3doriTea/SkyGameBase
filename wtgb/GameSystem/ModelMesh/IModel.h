#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// モデルのインタフェースクラス
	/// </summary>
	class IModel
	{
	public:
		IModel() {}
		virtual ~IModel() {}

		/// <summary>
		/// 試しにモデルを読み込む
		/// </summary>
		/// <param name="_fileName">ファイル名</param>
		/// <returns>ロード結果</returns>
		virtual HRESULT TryLoad(const std::string& _fileName) = 0;
	};
}
