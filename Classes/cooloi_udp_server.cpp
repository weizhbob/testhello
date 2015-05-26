#include "cooloi_udp_server.h"

namespace cooloi {

namespace udp {

Server::Server() {
	if ((sock_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		std::cout << "socket error" << std::endl;
	}

	const int opt = 1;
	int ssopt = 0;
	ssopt = setsockopt(sock_, SOL_SOCKET, SO_BROADCAST, (char*) &opt,
			sizeof(opt));
	if (ssopt == -1) {
		std::cout << "set socket error" << std::endl;
	}

	bzero(&addrto_, sizeof(struct sockaddr_in));
	addrto_.sin_family = AF_INET;
	addrto_.sin_addr.s_addr = htonl(INADDR_BROADCAST);
	addrto_.sin_port = htons(6000);
}

Server::~Server() {
}

void Server::Send(std::string str) {
	int nlen = sizeof(addrto_);

	while (true) {
		sleep(1);
		const char* smsg = str.c_str();
		int ret = sendto(sock_, smsg, strlen(smsg), 0, (sockaddr*) &addrto_,
				nlen);
	}
}

}

}
