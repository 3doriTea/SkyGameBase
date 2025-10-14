#pragma once
#include "pch/pch.h"

namespace wtgb
{
	template<typename ValueT, std::unsigned_integral HandleT = uint32_t>
	class HandlerCollection : protected std::map<HandleT, ValueT>
	{
	public:
		using std::map<HandleT, ValueT>::map;
		~HandlerCollection();

		/// <summary>
		/// ハンドラを追加 (登録する)
		/// </summary>
		/// <typeparam name="...Args">追加するときに渡すコンストラクタ引数の型</typeparam>
		/// <param name="...args">追加するときに渡すコンストラクタ引数</param>
		/// <returns>追加されたハンドラ</returns>
		template<typename ...Args>
		HandleT Emplace(Args&& ...args);
		/// <summary>
		/// ハンドラを無効化する
		/// </summary>
		/// <param name="_handle">無効化するハンドル</param>
		/// <returns></returns>
		bool Remove(const HandleT _handle);
		/// <summary>
		/// ハンドラを全て解放する
		/// </summary>
		void Release();
		/// <summary>
		/// 登録されているハンドラが空っぽか
		/// </summary>
		/// <returns>空っぽである true / false</returns>
		bool IsEmpty() const { return this->counter_ <= 0; }

		/// <summary>
		/// 頭イテレータ取得
		/// </summary>
		/// <returns>頭イテレータ</returns>
		std::map<HandleT, ValueT>::iterator begin() { return this->begin(); }
		/// <summary>
		/// 尾イテレータ取得
		/// </summary>
		/// <returns>尾イテレータ</returns>
		std::map<HandleT, ValueT>::iterator end() { return this->end(); }

		ValueT Get(const HandleT _handle);
	private:
		HandleT counter_{};
	};
}

template<typename ValueT, std::unsigned_integral HandleT>
template<typename ...Args>
HandleT wtgb::HandlerCollection<ValueT, HandleT>::Emplace(Args&& ...args)
{
	this->insert(std::pair<HandleT, ValueT>{ ++counter_, ValueT{ std::move(args...) } });
	return HandleT();
}

template<typename ValueT, std::unsigned_integral HandleT>
wtgb::HandlerCollection<ValueT, HandleT>::~HandlerCollection()
{
}

template<typename ValueT, std::unsigned_integral HandleT>
bool wtgb::HandlerCollection<ValueT, HandleT>::Remove(const HandleT _handle)
{
}

template<typename ValueT, std::unsigned_integral HandleT>
void wtgb::HandlerCollection<ValueT, HandleT>::Release()
{

}

template<typename ValueT, std::unsigned_integral HandleT>
inline ValueT wtgb::HandlerCollection<ValueT, HandleT>::Get(const HandleT _handle)
{
	return this[_handle];
}
