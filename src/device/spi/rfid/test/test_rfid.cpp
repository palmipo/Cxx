#include "raspispi.h"
#include "spiexception.h"
#include "mfrc522.h"
#include <cstdint>
#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
try
{
RaspiSpi spi(argv[1]);
MFRC522 rfid(&spi);
uint8_t a, b;
rfid.VersionReg(&a, &b);

std::stringstream ss;
ss << "version : " << (int)a << ", " << (int)b;
std::cout << ss.str() << std::endl;
}
catch (SPIExecption)
{
}

return 0;
}
