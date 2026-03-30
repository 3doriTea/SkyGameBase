#pragma once
#include <wtgb.h>

/// <summary>
/// 普通の単一jsonを読み込むクラス
/// </summary>
template<typename T>
class JsonUnitLoaderBase
{
public:
	JsonUnitLoaderBase(const fs::path& _jsonFile);
	~JsonUnitLoaderBase() = default;

	/// <summary>
	/// <para>試しに読み込む</para>
	/// <para>NOTE: これはoverrideしないでください!!!!!</para>
	/// </summary>
	/// <param name="_writeTo">書き込む先の構造体</param>
	/// <returns>読み込みに成功 true / false</returns>
	virtual bool TryLoad(T* _writeTo) final;

protected:
	/// <summary>
	/// 読み込む処理
	/// </summary>
	/// <param name="_json">json</param>
	/// <param name="_writeTo">書き込む構造体のポインタ渡し</param>
	virtual void OnLoad(const json& _json, T* _writeTo) = 0;

private:
	fs::path jsonFile_;
};

#include "JsonUnitLoaderBase.inl"
