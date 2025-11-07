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
		InnerMap::iterator begin() { return innerMap.begin(); }
		/// <summary>
		/// 尾イテレータ取得
		/// </summary>
		/// <returns>尾イテレータ</returns>
		InnerMap::iterator end() { return innerMap.end(); }

		std::remove_pointer_t<ValueT>& At(const HandleT _handle);
		const std::remove_pointer_t<ValueT>& At(const HandleT _handle) const;
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
inline std::remove_pointer_t<ValueT>& wtgb::HandlerCollection<ValueT, HandleT>::At(const HandleT _handle)
{
	assert(_handle != INVALID_HANDLE && "無効なハンドル値に参照されました");
	if (_handle == INVALID_HANDLE)
	{
		throw "無効なハンドル値に参照されました";
	}

	auto& valueRef{ innerMap.at(_handle) };
	if constexpr (std::is_pointer_v<ValueT>)
	{
		// ValueTがポインタの場合は実態を返す
		return *valueRef;
	}
	else
	{
		// ポインタでなければそのまま返す
		return valueRef;
	}
}

template<typename ValueT, std::unsigned_integral HandleT>
inline const std::remove_pointer_t<ValueT>& wtgb::HandlerCollection<ValueT, HandleT>::At(const HandleT _handle) const
{
	assert(_handle != INVALID_HANDLE && "無効なハンドル値に参照されました");
	if (_handle == INVALID_HANDLE)
	{
		throw "無効なハンドル値に参照されました";
	}

	auto& valueRef{ innerMap.at(_handle) };
	if constexpr (std::is_pointer_v<ValueT>)
	{
		// ValueTがポインタの場合は実態を返す
		return *valueRef;
	}
	else
	{
		// ポインタでなければそのまま返す
		return valueRef;
	}
}

