// 1.����json_vc71_libmtd.lib����Ŀ�ļ����� 2.�������ԣ���MFC��ʹ�þ�̬��
#pragma once
#include "include\json\json.h"
#include<fstream>
#include <string>
#pragma comment(lib,"json_vc71_libmtd.lib")

class JsonClass
{
public:
	JsonClass();
	~JsonClass();
	Json::Value GetJsonFromFile(const char* fileName);
	Json::Value ReadJson(std::string strS);
};

