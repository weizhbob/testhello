#ifndef cooloi_udp_client_class
#define cooloi_udp_client_class

#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <memory.h>
#include <cassert>

namespace cooloi {

namespace udp {

class Client {
public:
	Client();
	~Client();
	static Client* create();
	std::string UdpRecv();

private:
	int sock_;
	struct sockaddr_in from;
	struct sockaddr_in addrto;
};

}

}

#endif
