#pragma once

namespace wtgb
{
	/// <summary>
	/// 結果を表現する構造体
	/// </summary>
	struct Result
	{
		/// <summary>
		/// 結果コード
		/// </summary>
		enum struct Code : int
		{
			Failed = -2,
			Error = -1,
			Ok = 0,
			Succeed = 1,
		};

		Result(const bool _succeed) :
			code{ _succeed }
		{}

		Result(const Code _code) :
			code{ static_cast<int>(_code) }
		{}

		int code;  // 結果コード
	};
}
