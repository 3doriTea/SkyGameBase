#pragma once
#include "LibHeader/NlohmannJson.h"

namespace wtgb
{
	/// <summary>
	/// jsonの値を安全に取得する
	/// </summary>
	/// <typeparam name="T">値の型</typeparam>
	/// <param name="_j">Json</param>
	/// <param name="_key">キー</param>
	/// <returns>値</returns>
	template<typename T>
	T SafeGet(json& _j, const std::string_view _key);

	/// <summary>
	/// jsonの値を安全に取得する
	/// </summary>
	/// <typeparam name="T">値の型</typeparam>
	/// <param name="_j">Json</param>
	/// <param name="_key">キー</param>
	/// <param name="_defaultValue">取得できなかった時のデフォルトの値</param>
	/// <returns>値</returns>
	template<typename T>
	T SafeGet(json& _j, const std::string_view _key, const T _defaultValue);
}

template<typename T>
T wtgb::SafeGet(json& _j, const std::string_view _key)
{
	if (_j.contains(_key))
	{
		return _j.at(_key).get<T>();
	}
	else
	{
		return T{};
	}
}

template<typename T>
T wtgb::SafeGet(json& _j, const std::string_view _key, const T _defaultValue)
{
	if (_j.contains(_key))
	{
		return _j.at(_key).get<T>();
	}
	else
	{
		return _defaultValue;
	}
}
