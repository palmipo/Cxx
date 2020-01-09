// #include "socketfactory.h"
#include "canopen.h"
#include "pollexception.h"

#include <iostream>
#include <iomanip>
#include <sstream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
		std::stringstream ss;
		ss << argv[0] << " <if>";
		Log::getLogger()->debug(__FILE__, __LINE__, ss.str());
    }

    try
    {
        // Socket::SocketFactory factory;
		CANOpen * sock = new CANOpen();
        if (sock)
        {
			sock->connexion(argv[1]);
			
			uint8_t cmd[] = { 0x81, 0, 0, 0, 0, 0, 0, 0, 0 };
			sock->write(cmd, 9);

			uint8_t msg[512];
            // if (factory.scrute(10000) > 0)
			{
				s32 len = sock->read(msg, 512);
			}
        }
    }
    catch(PollException e)
    {
        Log::getLogger()->debug(__FILE__, __LINE__, e.what());
    }

    return 0;
}
