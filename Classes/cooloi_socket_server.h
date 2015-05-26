#ifndef Cooloi_Socket_Server_class
#define Cooloi_Socket_Server_class

#include "cooloi_socket.h"
#include "cooloi_openssl.h"
#include "cooloi_json.h"
#include "cooloi_file.h"
#include "cooloi_udp_server.h"
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <ifaddrs.h>

namespace cooloi{

namespace sockets{

class Server : public cooloi::sockets::Socket
{
public:
    Server();
    virtual ~Server();
    void Accept();
    void Run();
    void Send();
    std::string Recv();
private:
    int port_;
    std::string jsip;
	cooloi::Openssl ssl;
	cooloi::File files;
	cooloi::Json* json_ = cooloi::Json::create();
    std::string IntToString(int);
	std::string GetTime();
    std::string GetIP();
    void UdpSend();
	cooloi::sockets::Socket * clientsocket = new cooloi::sockets::Socket;
};

}

}

#endif
