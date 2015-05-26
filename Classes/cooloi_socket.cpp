#include "cooloi_socket.h"

namespace cooloi {

namespace sockets {

Socket::Socket() :
		m_sock_(-1) {
	memset(&m_addr_, 0, sizeof(m_addr_));
} //Socket::Socket

Socket::~Socket() {
	if (IsValid())
		::close(m_sock_);
} // Socket::~Socket

#pragma mark - Server initialization

int Socket::Create() {
	m_sock_ = socket(AF_INET, SOCK_STREAM, 0);

	if (!IsValid())
		return -1;

	// TIME_WAIT - argh
	int on = 1;
	if (-1
			== setsockopt(m_sock_, SOL_SOCKET, SO_REUSEADDR, (const char*) &on,
					sizeof(on)))
		return -1;

	return 0;
} // Socket::Create

int Socket::Bind(const int port) {
	if (!IsValid()) {
		return -1;
	}

	m_addr_.sin_family = AF_INET;
	m_addr_.sin_addr.s_addr = INADDR_ANY;
	m_addr_.sin_port = htons(port);

	int bind_return = ::bind(m_sock_, (struct sockaddr *) &m_addr_,
			sizeof(m_addr_));

	if (bind_return == -1) {
		return -1;
	}

	return 0;
} // Socket::Bind

int Socket::Listen() const {
	if (!IsValid()) {
		return -1;
	}

	int listen_return = ::listen(m_sock_, kMaxConnections);

	if (listen_return == -1) {
		return -1;
	}

	return 0;
} // Socket::Listen

int Socket::Accept(Socket& new_socket) const {
	int addr_length = sizeof(new_socket.m_addr_);
	new_socket.m_sock_ = ::accept(m_sock_, (sockaddr *) &new_socket.m_addr_,
			(socklen_t *) &addr_length);
	if (new_socket.m_sock_ <= 0)
		return -1;
	else
		return 0;
} // Socket::Accept

#pragma mark - Client initialization

int Socket::Connect(const std::string& host, const int port) {
	if (!IsValid())
		return -1;

	m_addr_.sin_family = AF_INET;
	m_addr_.sin_port = htons(port);
	m_addr_.sin_addr.s_addr = inet_addr(host.c_str());

	int status = ::connect(m_sock_, (sockaddr *) &m_addr_, sizeof(m_addr_));

	if (status == 0)
		return 0;
	else
		return -1;
} // Socket::Connect

#pragma mark - Data transimission

int Socket::Send(Socket &socket, const std::string& msg) {
	int status = ::send(socket.m_sock_, msg.c_str(), msg.size(), MSG_NOSIGNAL);
	if (status == -1) {
		return -1;
	} else {
		return 0;
	}
} // Socket::Send

int Socket::Recv(Socket &socket, std::string& msg) {
	char buf[kMaxRecv + 1];

	msg.clear();

	memset(buf, 0, kMaxRecv + 1);

	int status = ::recv(socket.m_sock_, buf, kMaxRecv, 0);

	if (status == -1) {
		std::cout << "status == -1   errno == " << errno
				<< "  in Socket::recv\n";
		return 0;
	} else if (status == 0) {
		return 0;
	} else {
		std::string s(&buf[0], &buf[status]);
		msg = s;
		return status;
	}
} // Socket::Recv

#pragma mark - Socket operation

void Socket::SetNonBlocking(const bool flag) {
	if (IsValid()) {
		int opts;

		opts = fcntl(m_sock_, F_GETFL); //设置文件描述符标志

		if (opts < 0) {
			return;
		}

		if (flag)
			opts = (opts | O_NONBLOCK); //设置成非阻塞模式
		else
			opts = (opts & ~O_NONBLOCK); //设置成阻塞模式

		fcntl(m_sock_, F_SETFL, opts);
	}
} // Socket::SetNonBlocking

int Socket::IsValid() const {
	return m_sock_ != -1;
}

int Socket::GetAddress() const {
	return m_addr_.sin_addr.s_addr;
} // Getaddress

int Socket::GetPort() const {
	return m_addr_.sin_port;
}

}

}
