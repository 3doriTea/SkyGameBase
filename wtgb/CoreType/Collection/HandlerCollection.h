#pragma once
#include "pch/pch.h"

// TODO: 重複をチェックする関数を抽象化する

namespace wtgb
{
	// 無効なハンドル値
	const uint32_t INVALID_HANDLE{ 0 };

	template<typename ValueT, std::unsigned_integral HandleT = uint32_t>
	class HandlerCollection
	{
	private:
		using InnerMap = std::map<HandleT, ValueT>;
	public:
		HandlerCollection();
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
		void Release(const std::function<void(ValueT& _value)>& _callback = [](ValueT& _value){});
		/// <summary>
		/// 登録されているハンドラが空っぽか
		/// </summary>
		/// <returns>空っぽである true / false</returns>
		bool IsEmpty() const { return this->counter_ <= 0; }

		/// <summary>
		/// 頭イテレータ取得
		/// </summary>
		/// <returns>頭イテレータ</returns>
		std::map<HandleT, ValueT>::iterator begin() { return innerMap.begin(); }
		/// <summary>
		/// 尾イテレータ取得
		/// </summary>
		/// <returns>尾イテレータ</returns>
		std::map<HandleT, ValueT>::iterator end() { return innerMap.end(); }

		ValueT& At(const HandleT _handle);
		const ValueT& At(const HandleT _handle) const;
	private:
		InnerMap innerMap{};
		HandleT counter_{};
	};
}

template<typename ValueT, std::unsigned_integral HandleT>
template<typename ...Args>
HandleT wtgb::HandlerCollection<ValueT, HandleT>::Emplace(Args&& ...args)
{
	innerMap.insert(std::pair<HandleT, ValueT>{ ++counter_, ValueT{ args... } });
	return counter_;
}

template<typename ValueT, std::unsigned_integral HandleT>
inline wtgb::HandlerCollection<ValueT, HandleT>::HandlerCollection() :
	innerMap{},
	counter_{}
{
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
void wtgb::HandlerCollection<ValueT, HandleT>::Release(const std::function<void(ValueT& _value)>& _callback)
{
	for (auto& pair : *this)
	{
		_callback(pair.second);
	}
}

template<typename ValueT, std::unsigned_integral HandleT>
inline ValueT& wtgb::HandlerCollection<ValueT, HandleT>::At(const HandleT _handle)
{
	return innerMap.at(_handle);
}

template<typename ValueT, std::unsigned_integral HandleT>
inline const ValueT& wtgb::HandlerCollection<ValueT, HandleT>::At(const HandleT _handle) const
{
	return innerMap.at(_handle);
}

