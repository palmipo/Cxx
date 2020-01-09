#include "rs232.h"
#include "rs232factory.h"
#include "rs232exception.h"
#include <iostream>
#include <thread>

int main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << argv[0] << " <device>" << std::endl;
		return -1;
	}

    try
    {
        RS232Factory factory;
        RS232 * serial = factory.add(argv[1]);
        if (serial)
        {
            serial->setConfig(B19200, 8, 'E', 1);
			
			{
				int32_t fin = 0;
				uint16_t fwst = 0;
				while (fwst != 9)
				{
					// FWST a READY ??
					uint8_t query[] = { 0x2, 0x3, 0xFF, 0xDB, 0x00, 0x01, 0xC4, 0x16 };
					serial->write(query, 8);
					while (factory.scrute(1000) > 0)
					{
						uint8_t rcv[100];
						int32_t len = serial->read(rcv, 100);
						fwst = (rcv[3] << 8) | rcv[4];
					}
				}
				while (!fin)
				{
					// FWST a READY ??
					uint8_t query[] = { 0x2, 0x3, 0xFF, 0xDB, 0x00, 0x01, 0xC4, 0x16 };
					serial->write(query, 8);
					while (factory.scrute(1000) > 0)
					{
						uint8_t rcv[100];
						int32_t len = serial->read(rcv, 100);
						fwst = (rcv[3] << 8) | rcv[4];
					}
					
					if (fwst == 3)
					{
						{
							// MODE a TP
							uint8_t cmd[] = { 0x2, 0x6, 0x5, 0xdc, 0x54, 0x50, 0x79, 0x33 };
							serial->write(cmd, 8);
							while (factory.scrute(1000) > 0)
							{
								uint8_t rcv[100];
								int32_t len = serial->read(rcv, 100);
							}
						}

						{
							// FWCD a APPLY
							uint8_t cmd[] = { 0x2, 0x6, 0xFF, 0xDA, 0x00, 0x02, 0x19, 0xD7 };
							serial->write(cmd, 8);
							while (factory.scrute(1000) > 0)
							{
								uint8_t rcv[100];
								int32_t len = serial->read(rcv, 100);
							}
						}
					}
					else if (fwst == 5)
					{
						{
							// MODE a TP
							uint8_t cmd[] = { 0x2, 0x6, 0x5, 0xdc, 0x54, 0x50, 0x79, 0x33 };
							serial->write(cmd, 8);
							while (factory.scrute(1000) > 0)
							{
								uint8_t rcv[100];
								int32_t len = serial->read(rcv, 100);
							}
						}

						{
							// FWCD a CLEAR
							uint8_t cmd[] = { 0x2, 0x6, 0xFF, 0xDA, 0x00, 0x03, 0xD8, 0x17 };
							serial->write(cmd, 8);
							while (factory.scrute(1000) > 0)
							{
								uint8_t rcv[100];
								int32_t len = serial->read(rcv, 100);
							}
						}
					}
					else if (fwst == 4)
					{
						fin = 1;
					}
				}
			}
        }
    }
    catch(RS232Exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
