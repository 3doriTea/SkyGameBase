#pragma once

namespace wtgb
{
	/// <summary>
	/// コンポーネントプールのインタフェース
	/// </summary>
	class IComponentPool
	{
	public:
		IComponentPool() {}
		virtual ~IComponentPool() {}

		/// <summary>
		/// コンポーネントプール内を破棄する
		/// </summary>
		virtual void Clear() = 0;
	};
}