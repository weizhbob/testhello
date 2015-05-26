#include "cooloi_socket_server.h"

namespace cooloi{

namespace sockets{

Server::Server() {
	if (cooloi::sockets::Socket::Create()) {
		std::cout << "Could not create server socket." << std::endl;
	} else {
		std::cout << "New Socket created" << std::endl;
	}
	for (port_ = 20000; port_ < 20010; port_++) {
		if (cooloi::sockets::Socket::Bind(port_) == 0) {
			std::string ports = IntToString(port_);
			std::string ip = GetIP();
			std::string str = json_->WriteJson(ip, ports);
			files.WriteFile(str, "Address.json");
			std::thread t(&Server::UdpSend, this);
			t.detach();
			break;
		}
	}
	if (port_ == 20010) {
		std::cout << "Could not bind to socket." << std::endl;
	}
	if (cooloi::sockets::Socket::Listen()) {
		std::cout << "Could not listen to socket." << std::endl;
	} else {
		std::cout << "Listen Start" << std::endl;
	}
}

Server::~Server() {
}

void Server::Accept() {
	if (cooloi::sockets::Socket::Accept(*clientsocket)) {
		std::cout << "Could not accept socket." << std::endl;
	}
}

void Server::Run() {
	Accept();
}

void Server::Send() {
	std::string msg = json_->WriteJson("Server ", "Send", GetTime());
	msg = ssl.ServerEncodeFile(msg);
	cooloi::sockets::Socket::Send(*clientsocket, msg);
}

std::string Server::Recv() {
	std::string msg;
	cooloi::sockets::Socket::Recv(*clientsocket, msg);
	msg = ssl.ServerDecodeFile(msg);
	msg = json_->ReadData(msg);
	return msg;
}

std::string Server::IntToString(int i) {
	std::stringstream s;
	s << i;
	return s.str();
}

std::string Server::GetTime() {
	std::string s;
	char stime[256] = { 0 };
	time_t now_time;
	time(&now_time);
	strftime(stime, sizeof(stime), "%H:%M:%S", localtime(&now_time));
	s = stime + '\0';
	return s;
}

std::string Server::GetIP() {
	struct ifaddrs * ifAddrStruct = NULL;
	struct ifaddrs * ifa = NULL;
	void * tmpAddrPtr = NULL;
	std::string s;
	getifaddrs(&ifAddrStruct);

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
		if (!ifa->ifa_addr)
			continue;
		if (ifa->ifa_addr->sa_family == AF_INET) {
			tmpAddrPtr = &((struct sockaddr_in *) ifa->ifa_addr)->sin_addr;
			char addressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
			char* p = ifa->ifa_name;
			s = addressBuffer;
			if(s != "" && s != "127.0.0.1")
				break;
		}
	}
	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);
	return s;
}

void Server::UdpSend() {
	cooloi::udp::Server us;
	std::string s = files.ReadFile("Address.json");
	us.Send(s);
}

}

}
