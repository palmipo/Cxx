#include "colecovision.h"
#include <cstdint>

int main(int argc, char **argv)
{
int32_t pin_out[] = { 1, 2, 3 };
int32_t pin_in[] = { 4, 5, 6, 7, 8 };

RaspiGpioFactory fact("/dev/chipgpio0");
RaspiGpio * out = fact->outputs(pin_out, 3);
RaspiGpio * in = fact->intputs(pin_in, 5);

ColecoVision coleco(out, in);
coleco->read();

return 0;
}
