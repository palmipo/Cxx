#include "socketfactory.h"
#include "socketexception.h"
#include "sockettcpfifo.h"
#include <cerrno>

Socket::SocketFactory::SocketFactory()
: PollFactory()
{
}

Socket::SocketFactory::~SocketFactory()
{}

Socket::SocketTcp * Socket::SocketFactory::addTcpServer(const std::string & addr, uint16_t port)
{
	try
	{
		return getTcp(addr, port);
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
		return (Socket::SocketTcp *)getTcp(addr, port);
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

Socket::SocketTcpFifo * Socket::SocketFactory::addTcpFifoConnection(const std::string & addr, uint16_t port)
{
	try
	{
		return (Socket::SocketTcpFifo *)getTcp(addr, port);
	}
	catch(...)
	{
		Socket::SocketTcpFifo * sock = new Socket::SocketTcpFifo();
		sock->connexion(addr, port);

		_hosts[std::pair<std::string, uint16_t>(addr, port)] = sock->handler();
		add(sock);

		return sock;
	}

	return 0;
}

Socket::SocketTcp * Socket::SocketFactory::getTcp(const std::string & addr, uint16_t port)
{
	std::map<std::pair<std::string, uint16_t>, int32_t>::iterator it = _hosts.find(std::pair<std::string, uint16_t>(addr, port));
	if (it != _hosts.end())
	{
		return (Socket::SocketTcp *)PollFactory::get(it->second);
	}
	
	throw Socket::SocketException(__FILE__, __LINE__, "not find");
}

void Socket::SocketFactory::delTcp(const std::string & addr, uint16_t port)
{
	std::map<std::pair<std::string, uint16_t>, int32_t>::iterator it = _hosts.find(std::pair<std::string, uint16_t>(addr, port));
	if (it != _hosts.end())
	{
		PollFactory::del(it->second);
		_hosts.erase(it);
	}
	
	throw Socket::SocketException(__FILE__, __LINE__, "not find");
}

int32_t Socket::SocketFactory::actionError(PollDevice * device)
{
	return device->actionError();
}

int32_t Socket::SocketFactory::actionIn(PollDevice * device)
{
	Socket::SocketBase * base = (Socket::SocketBase*)device;
	if (base->isServerMode())
	{
		// demande de connexion sur la socket d'ecoute
		Socket::SocketTcp * s = new Socket::SocketTcp(device->handler());
		add(s);
	}
	else
	{
		return device->actionIn();
	}
}

int32_t Socket::SocketFactory::actionOut(PollDevice * device)
{
	return device->actionOut();
}

