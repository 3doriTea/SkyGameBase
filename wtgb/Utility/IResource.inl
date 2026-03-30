#pragma once

template<typename... Args>
inline wtgb::IResource<Args...>::~IResource()  
{
#ifdef _DEBUG  
	if (!isReleased_)  
	{
		LOGFLN("::warn::リソースを解放せずにデストラクタが呼ばれている\n{}", GetStackTrace(2));  
		//wassert(isReleased_ && "リソースを解放せずにデストラクタが呼ばれている");  
	}
#endif
}
