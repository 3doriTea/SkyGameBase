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

		/// <summary>
		/// コンポーネントプールの要素を1つ破棄する
		/// </summary>
		/// <param name="_index">指定する要素のインデクス</param>
		virtual void ClearAt(const size_t _index) = 0;
	};
}