#pragma once
#include "pch/pch.h"

namespace wtgb
{
	/// <summary>
	/// 本体への直接アクセスをさせず、分離させる基底クラス
	/// </summary>
	/// <typeparam name="T">本体の型</typeparam>
	template<typename T>
	class Accessor
	{
	public:
		Accessor(T* _pTarget);
		virtual ~Accessor() {};

	protected:
		/// <summary>
		/// 本体のポインタを取得
		/// </summary>
		/// <returns>本体のポインタ</returns>
		T* GetAccess() const;

	private:
		T* target_;  //　アクセス先のポインタ
	};
}

template<typename T>
inline wtgb::Accessor<T>::Accessor(T* _pTarget) :
	target_{ _pTarget }
{
	//assert(_pTarget && "アクセス先指定でnullptrは無効");
}
template<typename T>
inline T* wtgb::Accessor<T>::GetAccess() const
{
	assert(target_ && "nullptrにアクセスしようとした");
	return target_;
}
