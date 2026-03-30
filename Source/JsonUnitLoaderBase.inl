#include "JsonUnitLoaderBase.h"

template<typename T>
inline JsonUnitLoaderBase<T>::JsonUnitLoaderBase(const fs::path& _jsonFile) :
	jsonFile_{ _jsonFile }
{
}

template<typename T>
inline bool JsonUnitLoaderBase<T>::TryLoad(T* _writeTo)
{
	if (!fs::is_regular_file(jsonFile_))
	{
		wassert(fs::is_regular_file(jsonFile_)
			&& "無効なファイルが指定されました。");
		return false;
	}

	json j{};
	std::ifstream ifs{ jsonFile_ };
	
	if (!ifs)
	{
		wassert(ifs && "ファイルの読み込みに失敗");
		return false;
	}
	
	ifs >> j;

	try
	{
		OnLoad(j, _writeTo);
	}
	catch (const json::exception& ex)
	{
		LOGFLN("Json Load Error:{}", ex.what());
		// 何らかしらの例がスローのため変換失敗
		return false;
	}

	return true;
}
