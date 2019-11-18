#include "socketbase.h"

/* constructeur socket client */
Socket::SocketBase::SocketBase()
: PollDevice()
, _srv_mode(0)
{}

/* constructeur socket serveur */
Socket::SocketBase::SocketBase(const std::string & addr, int16_t port)
: PollDevice()
, _srv_mode(1)
{}

Socket::SocketBase::~SocketBase()
{
}

int32_t Socket::SocketBase::isServerMode() const
{
    return _srv_mode;
}
