#include "mcp23017.h"
#include "i2c.h"


//~ const uint8_t IOCON[PORT][BANK]   = {{(port = 0 / bank = 0), (port = 0 / bank = 1)}, {(port = 1 / bank = 0), (port = 1 / bank = 1)}};
const uint8_t IODIR[2][2]   = {{0x00, 0x00}, {0x01, 0x10}};
const uint8_t IPOL[2][2]    = {{0x02, 0x01}, {0x03, 0x11}};
const uint8_t GPINTEN[2][2] = {{0x04, 0x02}, {0x05, 0x12}};
const uint8_t DEFVAL[2][2]  = {{0x06, 0x03}, {0x07, 0x13}};
const uint8_t INTCON[2][2]  = {{0x08, 0x04}, {0x09, 0x14}};
const uint8_t IOCON[2][2]   = {{0x0A, 0x05}, {0x0B, 0x15}};
const uint8_t GPPU[2][2]    = {{0x0C, 0x06}, {0x0D, 0x16}};
const uint8_t INTF[2][2]    = {{0x0E, 0x07}, {0x0F, 0x17}};
const uint8_t INTCAP[2][2]  = {{0x10, 0x08}, {0x11, 0x18}};
const uint8_t GPIO[2][2]    = {{0x12, 0x09}, {0x13, 0x19}};
const uint8_t OLAT[2][2]    = {{0x14, 0x0A}, {0x15, 0x1A}};

union GPIO_BIT
{
	struct ST_GPIO_BIT
	{
		uint8_t NOP:1;		// bit 0
		uint8_t INTPOL:1;
		uint8_t ODR:1;
		uint8_t HAEN:1;
		uint8_t DISSLW:1;
		uint8_t SEQOP:1;
		uint8_t MIRROR:1;
		uint8_t BANK:1;		// bit 7
	} bits;
	uint8_t octet;
};

MCP23017::MCP23017(uint8_t addr, I2C *ctrl)
: _bank(0)
, DeviceI2C(0x20 | (addr & 0x3), ctrl)
{
	GPIO_BIT gpio;
	uint8_t iocon = IOCON[0][0];
	_twi->transfert(_address, &iocon, 1, &gpio.octet, 1);

	_bank = gpio.bits.BANK;
}

MCP23017::~MCP23017()
{
	uint8_t bank[2]; bank[0] = IOCON[0][_bank]; bank[1] = 0;
	_twi->set(_address, bank, 2);
}

/*
The interrupt control module uses the following registers/bits:
• IOCON.MIRROR – controls if the two interrupt pins mirror each other
• GPINTEN – Interrupt enable register
• INTCON – controls the source for the IOC
• DEFVAL – contains the register default for IOC operation
*/
void MCP23017::init(uint8_t port, uint8_t dir, uint8_t pol, uint8_t pullup, uint8_t irq, uint8_t defval_pin, uint8_t defval)
{
	GPIO_BIT ctrl;
	
	// The MIRROR bit controls how the INTA and INTB pins function with respect to each other.
	// • When MIRROR = 1, the INTn pins are functionally OR’ed so that an interrupt on either port will cause both pins to activate.
	// • When MIRROR = 0, the INT pins are separated. Interrupt conditions on a port will cause its respective INT pin to activate.
	uint8_t registre = IOCON[port][_bank];
	_twi->transfert(_address, &registre, 1, &ctrl.octet, 1);

	ctrl.bits.BANK = _bank;
	ctrl.bits.SEQOP = 1;
	ctrl.bits.MIRROR = 1;
	ctrl.bits.INTPOL=0;
	ctrl.bits.ODR=0;

	uint8_t iocon[2];
	iocon[0] = IOCON[port][_bank];
	iocon[1] = ctrl.octet;
	_twi->set(_address, iocon, 2);

	// io dir
	uint8_t iodir[2];
	iodir[0] = IODIR[port][_bank];
	iodir[1] = dir;
	_twi->set(_address, iodir, 2);

	if (dir)
	{
		// ipol
		uint8_t ipol[2];
		ipol[0] = IPOL[port][_bank];
		ipol[1] = pol;
		_twi->set(_address, ipol, 2);

		// pull-up resistor
		uint8_t gppu[2];
		gppu[0] = GPPU[port][_bank];
		gppu[1] = pullup;
		_twi->set(_address, gppu, 2);

		// interrupt-on-change control register
		// 1 = Enables GPIO input pin for interrupt-on-change event.
		// 0 = Disables GPIO input pin for interrupt-on-change event.
		uint8_t gpinten[2];
		gpinten[0] = GPINTEN[port][_bank];
		gpinten[1] = irq;
		_twi->set(_address, gpinten, 2);

		// interrupt control register
		// 1 = Pin value is compared against the associated bit in the DEFVAL register.
		// 0 = Pin value is compared against the previous pin value.
		uint8_t intcon[2];
		intcon[0] = INTCON[port][_bank];
		intcon[1] = defval_pin;
		_twi->set(_address, intcon, 2);

		// default comparison value
		// DEF<7:0>: Sets the compare value for pins configured for interrupt-on-change from defaults
		uint8_t defval_reg[2];
		defval_reg[0] = DEFVAL[port][_bank];
		defval_reg[1] = defval;
		_twi->set(_address, defval_reg, 2);
	}
}

uint8_t MCP23017::getIrq(uint8_t port)
{
	// INTF
	// Reflects the interrupt condition on the port. It reflects the change only if interrupts are enabled per GPINTEN<7:0>.
	// 1 = Pin caused interrupt.
	// 0 = Interrupt not pending
	uint8_t value = 0;
	uint8_t intf = INTF[port][_bank];
	_twi->transfert(_address, &intf, 1, &value, 1);
	
	// INTCAP
	// Reflects the logic level on the port pins at the time of interrupt due to pin change <7:0>
	// 1 = Logic-high
	// 0 = Logic-low
	uint8_t intcap = INTCAP[port][_bank];
	_twi->transfert(_address, &intcap, 1, &value, 1);

	return value;
}

void MCP23017::set(uint8_t port, uint8_t buf)
{
	uint8_t cmd[2];
	cmd[0] = OLAT[port][_bank];
	cmd[1] = buf;

	_twi->set(_address, cmd, 2);
}

uint8_t MCP23017::get(uint8_t port)
{
	uint8_t value = 0;
	uint8_t cmd = GPIO[port][_bank];
	_twi->transfert(_address, &cmd, 1, &value, 1);

	return value;
}
