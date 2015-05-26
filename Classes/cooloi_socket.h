#ifndef cooloi_socket_class
#define cooloi_socket_class

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <memory.h>
#include <errno.h>
#include <iostream>
#include <string>

const auto kMaxHostName = 200;
const auto kMaxConnections = 5;
const auto kMaxRecv = 500;
const auto kHost = "localhost";
const auto kPort = 2333;

namespace cooloi {

namespace sockets {

class Socket {
private:
	int m_sock_;
	struct sockaddr_in m_addr_;

public:
	Socket();
	virtual ~Socket();

#pragma mark - Server initialization

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int Create();

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int Bind(const int port);

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int Listen() const;

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int Accept(Socket & clientSocket) const;

#pragma mark - Client initialization

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int Connect(const std::string& host, const int port);

#pragma mark - Data transimission

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	static int Send(Socket & socket, const std::string& message);

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	static int Recv(Socket & socket, std::string& message);

#pragma mark - CooloiSocket operation

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	void SetNonBlocking(const bool flag);

	///<summary>
	///
	///</summary>
	///<parm name = ""></parm>
	int IsValid() const;

#pragma mark - Get socket address and port
	int GetAddress() const;
	int GetPort() const;
};

}

}

#endif
