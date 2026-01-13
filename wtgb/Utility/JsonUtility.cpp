#include "JsonUtility.h"

bool wtgb::TryGet(const std::string_view _key, json** _ppDistJson, json& _srcJson)
{
	if (_srcJson.contains(_key))
	{
		*_ppDistJson = &_srcJson.at(_key);
		return true;
	}
	else
	{
		return false;
	}
}
