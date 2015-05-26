#include "cooloi_file.h"

namespace cooloi {

bool File::WriteFile(std::string str, std::string pFileName) {
	std::string path = cocos2d::CCFileUtils::getInstance()->getWritablePath() + pFileName;
	CCLOG("wanna save file path = %s", path.c_str());
	const char* pcout = str.c_str();
	FILE* file = fopen(path.c_str(), "wb");
	if (file) {
		fputs(pcout, file);
		fclose(file);
	}
	return false;
}

std::string File::ReadFile(std::string pFileName) {
	std::string path = cocos2d::CCFileUtils::getInstance()->getWritablePath() + pFileName;
	CCLOG("path = %s", path.c_str());
	FILE* file = fopen(path.c_str(), "rb+"); //创建一个文件指针
	if (file) {
		char* buf; //要获取的字符串
		int len; //获取的长度
		fseek(file, 0, SEEK_END); //移到尾部
		len = ftell(file); //提取长度
		rewind(file); //回归原位
		CCLOG("count the file content len = %d", len);
		buf = (char*) malloc(sizeof(char) * len + 1);
		if (!buf) {
			CCLOG("malloc space is not enough.");
			return NULL;
		}
		int rLen = fread(buf, sizeof(char), len, file);
		buf[rLen] = '\0';
		CCLOG("has read Length = %d", rLen);
		CCLOG("has read content = %s", buf);
		std::string result = buf;
		fclose(file);
		free(buf);
		return result;
	}
	return NULL;
}

}
