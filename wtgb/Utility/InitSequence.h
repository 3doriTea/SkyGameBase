#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// 一連の初期化処理を扱うクラス
	/// </summary>
	class InitSequence
	{
	public:
		/// <summary>
		/// 開始
		/// </summary>
		/// <returns></returns>
		static InitSequence& Begin();

		/// <summary>
		/// 試しに実行処理
		/// </summary>
		/// <param name="_callback"></param>
		/// <returns></returns>
		InitSequence& TryRun(const std::function<HRESULT()>& _callback, const std::string_view& _errorMessage);

		/// <summary>
		/// 終了
		/// </summary>
		/// <returns>終了コード</returns>
		HRESULT End();

	private:
		InitSequence();
		~InitSequence();

	private:
		HRESULT hResult_;
	};
}
