#include "cooloi_socket_client.h"

namespace cooloi{

namespace sockets{

Client::Client(const std::string& host,const int port)
{
	cooloi::sockets::Socket::Create();
	cooloi::sockets::Socket::Connect(host, port);
}

Client::~Client()
{

}

std::string Client::GetTime()
{
	std::string s;
	char stime[256] = {0};
	time_t now_time;
	time(&now_time);
	strftime(stime,sizeof(stime),"%H:%M:%S",localtime(&now_time));
	s = stime + '\0';
	return s;
}

void Client::Send(std::string SendMsg)
{
	std::string msg = js->WriteJson("Message", SendMsg, "(" + GetTime() + ")");
	std::string e_msg = cssl -> ClientEncodeFile(msg);
	cooloi::sockets::Socket::Send(static_cast<cooloi::sockets::Socket&>(*this), e_msg);
}

void Client::SendP() {
	std::string pstr = "";
	std::string msg = js->WriteJson("Picture", pstr, "(" + GetTime() + ")");
	std::string e_msg = cssl -> ClientEncodeFile(msg);
	cooloi::sockets::Socket::Send(static_cast<cooloi::sockets::Socket&>(*this), e_msg);
}

std::string Client::Recv() {
	std::string msg = "";
	std::string s = "";
	int i = cooloi::sockets::Socket::Recv(static_cast<cooloi::sockets::Socket&>(*this), s);
	if(i <= 0)
	{
		msg = "";
	}
	else
	{
		std::string d = cssl -> ClientDecodeFile(s);
		msg = js->ReadJson(d);
	}
	return msg;
}

}

}
