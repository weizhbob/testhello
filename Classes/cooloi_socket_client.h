#ifndef cooloi_socket_client_class
#define cooloi_socket_client_class


#include "cooloi_socket.h"
#include "cooloi_openssl.h"
#include "cooloi_json.h"
#include <iostream>
#include <string>

namespace cooloi{

namespace sockets{

class Client :public cooloi::sockets::Socket
{
public:
	Client(const std::string& host,const int port);
	virtual ~Client();
	void Run();
	void Send(std::string SendMsg);
	void SendP();
	std::string Recv();
	std::string GetTime();

private:
	static void* Recv_t(void *);
	int thread();
	static std::string _msg;
	cooloi::Json* js = cooloi::Json::create();
	cooloi::Openssl* cssl = cooloi::Openssl::create();
};

}

}

#endif
