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
	T SafeGet(const json& _j, const std::string_view _key);

	/// <summary>
	/// jsonの値を安全に取得する
	/// </summary>
	/// <typeparam name="T">値の型</typeparam>
	/// <param name="_j">Json</param>
	/// <param name="_key">キー</param>
	/// <param name="_defaultValue">取得できなかった時のデフォルトの値</param>
	/// <returns>値</returns>
	template<typename T>
	T SafeGet(const json& _j, const std::string_view _key, const T _defaultValue);

	/// <summary>
	/// 試しに値を取得する
	/// </summary>
	/// <param name="_key">要素のキー</param>
	/// <param name="_ppDistJson">取得した先の格納 jsonオブジェクトのポインタ</param>
	/// <param name="_srcJson">取得する元の jsonオブジェクト</param>
	/// <returns>取得できた true / false</returns>
	bool TryGet(const std::string_view _key, json** _ppDistJson, json& _srcJson);
}

template<typename T>
T wtgb::SafeGet(const json& _j, const std::string_view _key)
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
T wtgb::SafeGet(const json& _j, const std::string_view _key, const T _defaultValue)
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
