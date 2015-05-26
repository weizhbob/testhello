#ifndef cooloi_json_class
#define cooloi_json_class

#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#include <string>

namespace cooloi {

class Json {
public:
	static Json* create();
	std::string WriteJson(std::string name, std::string data, std::string time);
	std::string WriteJson(std::string ip, std::string port);
	std::string WriteJson(std::string data);
	std::string ReadJson(std::string str);
	std::string ReadData(std::string str);
	std::string ReadIP(std::string str);
	std::string ReadPort(std::string str);
};

}

#endif
