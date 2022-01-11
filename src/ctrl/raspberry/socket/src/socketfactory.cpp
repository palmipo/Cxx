#include "socketfactory.h"
#include "socketexception.h"
#include "sockettcp.h"
#include "socketudp.h"
#include <cerrno>

Socket::SocketFactory::SocketFactory()
: PollFactory()
{}

Socket::SocketFactory::~SocketFactory()
{}

Socket::SocketTcp * Socket::SocketFactory::addTcpServer(const std::string & addr, uint16_t port)
{
	try
	{
		return (Socket::SocketTcp *)get(addr, port);
	}
	catch(...)
	{
		Socket::SocketTcp * sock = new Socket::SocketTcp(addr, port);

		_hosts[std::pair<std::string, uint16_t>(addr, port)] = sock->handler();
		add(sock);

		return sock;
	}

	return 0;
}

Socket::SocketTcp * Socket::SocketFactory::addTcpConnection(const std::string & addr, uint16_t port)
{
	try
	{
		return (Socket::SocketTcp *)get(addr, port);
	}
	catch(...)
	{
		Socket::SocketTcp * sock = new Socket::SocketTcp();
		sock->connexion(addr, port);

		_hosts[std::pair<std::string, uint16_t>(addr, port)] = sock->handler();
		add(sock);

		return sock;
	}

	return 0;
}

Socket::SocketUdp * Socket::SocketFactory::addUdpConnection(const std::string & addr, uint16_t port)
{
	try
	{
		return (Socket::SocketUdp *)get(addr, port);
	}
	catch(...)
	{
		Socket::SocketUdp * sock = new Socket::SocketUdp();
		sock->connexion(addr, port);

		_hosts[std::pair<std::string, uint16_t>(addr, port)] = sock->handler();
		add(sock);

		return sock;
	}

	return 0;
}

Socket::SocketBase * Socket::SocketFactory::get(const std::string & addr, uint16_t port)
{
	std::map<std::pair<std::string, uint16_t>, int32_t>::iterator it = _hosts.find(std::pair<std::string, uint16_t>(addr, port));
	if (it != _hosts.end())
	{
		return (Socket::SocketBase *)PollFactory::get(it->second);
	}
	
	throw Socket::SocketException(__FILE__, __LINE__, "not find");
}

void Socket::SocketFactory::del(const std::string & addr, uint16_t port)
{
	std::map<std::pair<std::string, uint16_t>, int32_t>::iterator it = _hosts.find(std::pair<std::string, uint16_t>(addr, port));
	if (it != _hosts.end())
	{
		PollFactory::del(it->second);
		_hosts.erase(it);
	}
	else
	{
		throw Socket::SocketException(__FILE__, __LINE__, "not find");
	}
}

