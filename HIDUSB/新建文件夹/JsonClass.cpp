#include "stdafx.h"
#include "JsonClass.h"


JsonClass::JsonClass()
{
}


JsonClass::~JsonClass()
{
}

Json::Value JsonClass::GetJsonFromFile(const char* fileName)
{

	Json::Reader reader;
	std::ifstream file(fileName);

	file.is_open();
	Json::Value root;
	if (!reader.parse(file, root, false)) {

	}
	return root;

}
