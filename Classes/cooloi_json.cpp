#include "cooloi_json.h"

namespace cooloi {

Json* Json::create() {
	Json* ret = new Json();
	return ret;
}

std::string Json::WriteJson(std::string name, std::string data,
		std::string time) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	doc.AddMember("name", name.c_str(), allocator);
	doc.AddMember("data", data.c_str(), allocator);
	doc.AddMember("time", time.c_str(), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	msg = buffer.GetString();
	return msg;
}

std::string Json::WriteJson(std::string ip, std::string port) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	doc.AddMember("ip", ip.c_str(), allocator);
	doc.AddMember("port", port.c_str(), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	msg = buffer.GetString();
	return msg;
}

std::string Json::WriteJson(std::string data) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.SetObject();
	rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

	doc.AddMember("data", data.c_str(), allocator);

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	msg = buffer.GetString();
	return msg;
}

std::string Json::ReadJson(std::string str) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	if (doc.HasParseError()) {
		return "";
	}
	rapidjson::Value &v = doc;

	std::string name = "";
	std::string data = "";
	std::string time = "";
	if (v.HasMember("name") && v.HasMember("data") && v.HasMember("time")) {
		name = v["name"].GetString();
		data = v["data"].GetString();
		time = v["time"].GetString();
	}
	msg = name + ":" + data + "(" + time + ")";
	return msg;
}

std::string Json::ReadData(std::string str) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	if (doc.HasParseError()) {
		return "";
	}
	rapidjson::Value &v = doc;

	std::string data = "";
	if (v.HasMember("data")) {
		data = v["data"].GetString();
	}
	msg = data;
	return msg;
}

std::string Json::ReadIP(std::string str) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	if (doc.HasParseError()) {
		return "";
	}
	rapidjson::Value &v = doc;

	std::string ip = "";
	if (v.HasMember("ip")) {
		ip = v["ip"].GetString();
	}
	msg = ip;
	return msg;
}

std::string Json::ReadPort(std::string str) {
	std::string msg = "";
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(str.c_str());
	if (doc.HasParseError()) {
		return "";
	}
	rapidjson::Value &v = doc;

	std::string port = "";
	if (v.HasMember("port")) {
		port = v["port"].GetString();
	}
	msg = port;
	return msg;
}

}
