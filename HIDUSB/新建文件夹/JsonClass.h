#pragma once
#include "include\json\json.h"
#include<fstream>
#pragma comment(lib,"json_vc71_libmtd.lib")

class JsonClass
{
public:
	JsonClass();
	~JsonClass();
	Json::Value GetJsonFromFile(const char* fileName);
};

