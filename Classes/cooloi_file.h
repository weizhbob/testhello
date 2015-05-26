#ifndef Cooloi_File_Class
#define Cooloi_File_Class

#include "cocos2d.h"
#include <iostream>

namespace cooloi {

class File {
public:
	static std::string ReadFile(std::string); //读取本地文件，返回数据
	static bool WriteFile(std::string, std::string); //储存内容到文件
};

}

#endif
