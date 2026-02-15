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
	auto itr{ innerMap.find(_handle) };

	if (itr == innerMap.end())
	{
		// 見つからなかったため除去失敗
		return false;
	}
	else
	{
		// 見つかったため除去成功
		innerMap.erase(itr);
		return true;
	}
}

template<typename ValueT, std::unsigned_integral HandleT>
void wtgb::HandlerCollection<ValueT, HandleT>::Release(const std::function<void(ValueT& _value)>& _callback)
{
	for (auto& [handle, value] : *this)
	{
		// 解放前に周回する
		_callback(value);
	}

	// ちゃんと解放！
	innerMap.clear();
}

template<typename ValueT, std::unsigned_integral HandleT>
inline HandleT wtgb::HandlerCollection<ValueT, HandleT>::GetContainsDuplicate(const std::function<bool(ValueT& _value)>& _callback)
{
	for (auto& [handle, value] : *this)
	{
		if (_callback(value))
		{
			// 見つかった！
			return handle;
		}
	}

	// 指定ハンドルが見つからなかったため無効ハンドルを返す
	return wtgb::INVALID_HANDLE;
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
