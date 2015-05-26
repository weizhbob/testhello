#include "cooloi_udp_client.h"

namespace cooloi {

namespace udp {

Client::Client() {
	memset(&addrto, 0, sizeof(addrto));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_ANY);
	addrto.sin_port = htons(6000);

	memset(&from, 0, sizeof(from));
	from.sin_family = AF_INET;
	from.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sock_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		assert(false);
	}

	const int opt = 1;

	int nb = 0;
	nb = setsockopt(sock_, SOL_SOCKET, SO_BROADCAST, (char*) &opt, sizeof(opt));
	if (nb == -1) {
		assert(false);
	}
	if (bind(sock_, (struct sockaddr *) &(addrto), sizeof(struct sockaddr_in))
			== -1) {
		assert(false);
	}

}

Client::~Client() {

}

Client* Client::create() {
	Client* ret = new Client();
	return ret;
}

std::string Client::UdpRecv() {
	int recvlen = sizeof(from);
	char smsg[100] = { 0 };
	std::string recvMsg = "";

	int ret = recvfrom(sock_, smsg, 100, 0, (struct sockaddr*) &from,
			(socklen_t*) &recvlen);
	if (ret <= 0) {
		assert(false);
	} else {
		recvMsg = smsg;
	}
	return recvMsg;
}

}

}
