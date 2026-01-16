#pragma once
#include "Helper/CommonGameComponentPool.h"

namespace wtgb
{
	class Parameter;

	/// <summary>
	/// コンポーネントプール : ゲームオブジェクト固有の変数(Parameter)
	/// </summary>
	class CPParameter : public ComponentPool<Parameter>
	{
	public:
		inline CPParameter() {}
		inline ~CPParameter() {}

		/// <summary>
		/// 初期化処理
		/// </summary>
		inline void Init() override {}

		/// <summary>
		/// 更新処理
		/// </summary>
		inline void Update() override {}
	};
}
