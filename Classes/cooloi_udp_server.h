#ifndef UdpServer_class
#define UdpServer_class

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

namespace cooloi {

namespace udp {

class Server {
public:
	Server();
	~Server();
	void Send(std::string str);
private:
	int sock_;
	struct sockaddr_in addrto_;
};

}

}

#endif
