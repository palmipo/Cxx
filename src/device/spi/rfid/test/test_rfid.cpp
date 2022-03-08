#include "raspispi.h"
#include "spiexception.h"
#include "mfrc522.h"

int main(char **argv, int argc)
{
try
{
RaspiSpi spi(argv[1]);
MFRC522 rfid(&spi);
}
catch (SPIExecption)
{
}

return 0;
}
