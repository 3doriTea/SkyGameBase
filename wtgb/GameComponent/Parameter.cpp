#include "Parameter.h"
#include <fstream>
#include "WTGBAssert.h"

wtgb::Parameter::Parameter() :
	jsonFilePath_{},
	json_{}
{

}

const json& wtgb::Parameter::Load()
{
	json_ = {};

	wassert(fs::is_regular_file(jsonFilePath_) && "指定されたjsonファイルが存在しない");

	std::ifstream ifs{ jsonFilePath_ };
	ifs >> json_;

	wassert(json_.contains("Param") && "指定されたjsonファイル内にParamキーが存在しない");

	return json_.at("Param");
}
