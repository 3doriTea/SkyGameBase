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

		template<typename ...Args>
		HandleT Emplace(Args&& ...args);
		bool Remove(const HandleT _handle);
		void Release();

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
