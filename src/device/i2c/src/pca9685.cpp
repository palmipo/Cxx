#include "pca9685.h"
#include "pca9685led.h"
#include "i2c.h"

const uint8_t REG_MODE1 = 0x00;
const uint8_t REG_MODE2 = 0x01;
const uint8_t REG_SUBADR1 = 0x02;
const uint8_t REG_SUBADR2 = 0x03;
const uint8_t REG_SUBADR3 = 0x04;
const uint8_t REG_ALLCALLADR = 0x05;
const uint8_t REG_ALL_LED = 0xFA;
const uint8_t REG_PRESCALE = 0xFE;

const uint8_t MODE1_RESTART = 7;
const uint8_t MODE1_EXTCLK = 6;
const uint8_t MODE1_AI = 5;
const uint8_t MODE1_SLEEP = 4;
const uint8_t MODE1_SUB1 = 3;
const uint8_t MODE1_SUB2 = 2;
const uint8_t MODE1_SUB3 = 1;
const uint8_t MODE1_ALLCALL = 0;

const uint8_t MODE2_INVRT = 4;
const uint8_t MODE2_OCH = 3;
const uint8_t MODE2_OUTDRV = 2;
const uint8_t MODE2_OUTNE1 = 1;
const uint8_t MODE2_OUTNE0 = 0;

PCA9685::PCA9685(uint8_t addr, I2C * ctrl)
: DeviceI2C(0x40 | addr, ctrl)
, _mode1(0)
, _mode2(0)
, _clock(25000000)
{
	_leds = new PCA9685Led[16];

	setModes();
}

PCA9685::~PCA9685()
{
	delete[] _leds;
}

void PCA9685::reset()
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = REG_MODE1;
	cmd[1] = 0x00;
	_twi->set(_address, cmd, 2);
	delete[] cmd;
}

PCA9685Led *PCA9685::getLed(uint8_t num)
{
	return &_leds[num & 0x0F];
}

void PCA9685::read(uint8_t port)
{
	setAutoIncrement(1);
	
	uint8_t p = port & 0x0F;
	uint8_t cmd = 0x06 + 4 * p;
	uint8_t *rcv = new uint8_t[4];
	_twi->transfert(_address, &cmd, 1, rcv, 4);
	
	uint16_t v1 = rcv[1]<<8 | rcv[0];
	_leds[p].setOffsetON(v1);

	uint16_t v2 = rcv[3]<<8 | rcv[2];
	_leds[p].setOffsetOFF(v2);
}

void PCA9685::write(uint8_t port)
{
	setAutoIncrement(1);
	
	uint8_t *cmd = new uint8_t[5];

	// offset register LED0_ON_L
	uint8_t p = port & 0x0F;
	cmd[0] = 0x06 + 4 * p;

	// lecture valeur
	uint16_t u = _leds[p].getOffsetON();

	// LEDx_ON_L
	cmd[1] = u & 0x00FF;

	// LEDx_ON_H
	cmd[2] = (u & 0x0F00) >> 8;

	// lecture valeur
	uint16_t v= _leds[p].getOffsetOFF();

	// LEDx_OFF_L
	cmd[3] = v & 0x00FF;

	// LEDx_OFF_H
	cmd[4] = (v & 0x0F00) >> 8;

	_twi->set(_address, cmd, 5);
	delete[] cmd;
}

void PCA9685::writeAll()
{
	setAutoIncrement(1);
	
	uint8_t *cmd = new uint8_t[65];
	
	// offset register LED0_ON_L
	cmd[0] = 0x06;
	
	for (uint8_t i=0; i<16; ++i)
	{
		uint8_t offset = 4 * i + 1;
		
		uint16_t u = _leds[i].getOffsetON();

		// LEDx_ON_L
		cmd[offset] = u & 0x00FF;

		// LEDx_ON_H
		cmd[offset+1] = (u & 0x0F00) >> 8;

		uint16_t v= _leds[i].getOffsetOFF();

		// LEDx_OFF_L
		cmd[offset+2] = v & 0x00FF;

		// LEDx_OFF_H
		cmd[offset+3] = (v & 0x0F00) >> 8;
	}
	_twi->set(_address, cmd, 65);
	delete[] cmd;
}

void PCA9685::restart()
{
	//lecture des reg MODE1 & MODE2
	getModes();
	
	if (_mode1 & (1 << MODE1_RESTART))
	{
		_mode1 |= (1 << MODE1_SLEEP);
		setModes();
		
		// Util::sleep(500);
		
		_mode1 = (1 << MODE1_RESTART);
		setModes();
	}
}

void PCA9685::setExternalClock(uint8_t on_off, uint32_t frequency)
{
	_mode1 = _mode1 & ~(1 << MODE1_EXTCLK) | ((on_off & 0x01) << MODE1_EXTCLK);
	(on_off == 0) ? _clock = 25000000 : _clock = frequency;

	setModes();
}

uint8_t PCA9685::getAutoIncrement()
{
	getModes();
	return (_mode1 & (1 << MODE1_AI)) >> MODE1_AI;
}

void PCA9685::setAutoIncrement(uint8_t value)
{
	_mode1 = _mode1 & ~(1 << MODE1_AI) | ((value & 0x01) << MODE1_AI);
	setModes();
}

uint8_t PCA9685::getOutputChangeOnAck()
{
	getModes();
	return (_mode2 & (1 << MODE2_OCH)) >> MODE2_OCH;
}

void PCA9685::setOutputChangeOnAck(uint8_t value)
{
	_mode2 = _mode2 & ~(1 << MODE2_OCH) | ((value & 0x01) << MODE2_OCH);
	setModes();
}

void PCA9685::setAllLeds(uint16_t value_on, uint16_t value_off)
{
	uint8_t offset = 0;
	uint8_t *cmd = new uint8_t[5];
	
	// offset register ALL_LED_ON
	cmd[offset++] = REG_ALL_LED;
	
	// LEDx_ON_L
	cmd[offset++] = value_on & 0x00FF;

	// LEDx_ON_H
	cmd[offset++] = (value_on & 0x0F00) >> 8;

	// LEDx_OFF_L
	cmd[offset++] = value_off & 0x00FF;

	// LEDx_OFF_H
	cmd[offset++] = (value_off & 0x0F00) >> 8;

	_twi->set(_address, cmd, offset);
	delete[] cmd;
}

void PCA9685::setAllLedsOn()
{
	uint8_t *cmd = new uint8_t[5];
	cmd[0] = REG_ALL_LED;
	cmd[1] = 0x00;
	cmd[2] = 0x10;
	cmd[3] = 0x00;
	cmd[4] = 0x00;
	_twi->set(_address, cmd, 5);
	delete[] cmd;
}

void PCA9685::setAllLedsOff()
{
	uint8_t *cmd = new uint8_t[5];
	cmd[0] = REG_ALL_LED;
	cmd[1] = 0x00;
	cmd[2] = 0x00;
	cmd[3] = 0x00;
	cmd[4] = 0x10;
	_twi->set(_address, cmd, 5);
	delete[] cmd;
}

uint8_t PCA9685::getPrescaler()
{
	uint8_t cmd = REG_PRESCALE;
	uint8_t rcv = 0;
	_twi->transfert(_address, &cmd, 1, &rcv, 1);
	
	return rcv;
}

void PCA9685::setPrescaler(uint8_t value)
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = REG_MODE1;
	cmd[1] = _mode1 | (1<<MODE1_SLEEP);
	_twi->set(_address, cmd, 2);

	cmd[0] = REG_PRESCALE;
	cmd[1] = value;
	_twi->set(_address, cmd, 2);
	
	// Util::sleep(500);

	cmd[0] = REG_MODE1;
	cmd[1] = (1<<MODE1_RESTART) | (1<<MODE1_AI);
	_twi->set(_address, cmd, 2);
	delete[] cmd;
	
	// Util::sleep(500);
}

void PCA9685::setPwmFrequency(uint32_t frequency)
{
	float prescale = (float)_clock;
	prescale /= 4095;
	prescale /= (float)frequency;
	prescale -= 1;
	
	setPrescaler((uint8_t)(prescale + 0.5));
}

void PCA9685::setSubAddress1(uint8_t on_off, uint8_t value)
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = REG_SUBADR1;
	cmd[1] = value;
	_twi->set(_address, cmd, 2);
	delete[] cmd;
	
	_mode1 |= on_off << MODE1_SUB1;
	setModes();
}

void PCA9685::setSubAddress2(uint8_t on_off, uint8_t value)
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = REG_SUBADR2;
	cmd[1] = value;
	_twi->set(_address, cmd, 2);
	delete[] cmd;
	
	_mode1 |= on_off << MODE1_SUB2;
	setModes();
}

void PCA9685::setSubAddress3(uint8_t on_off, uint8_t value)
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = REG_SUBADR3;
	cmd[1] = value;
	_twi->set(_address, cmd, 2);
	delete[] cmd;
	
	_mode1 |= on_off << MODE1_SUB3;
	setModes();
}

void PCA9685::setAllCallAddress(uint8_t on_off, uint8_t value)
{
	uint8_t *cmd = new uint8_t[2];
	cmd[0] = 0x05;
	cmd[1] = value;
	_twi->set(_address, cmd, 2);
	delete[] cmd;

	_mode1 |= (on_off << MODE1_ALLCALL);
	setModes();
}

uint8_t PCA9685::getOutDrv()
{
	getModes();
	return (_mode2 & (1 << MODE2_OUTDRV)) >> MODE2_OUTDRV;
}

void PCA9685::setOutDrv(uint8_t value)
{
	_mode2 = _mode2 & ~(1 << MODE2_OUTDRV) | ((value & 0x01) << MODE2_OUTDRV);
	setModes();
}

uint8_t PCA9685::getInvertOutput()
{
	getModes();
	return (_mode2 & (1 << MODE2_INVRT)) >> MODE2_INVRT;
}

void PCA9685::setInvertOutput(uint8_t value)
{
	_mode2 = _mode2 & ~(1 << MODE2_INVRT) | ((value & 0x01) << MODE2_INVRT);
	setModes();
}

void PCA9685::getModes()
{
	uint8_t cmd = REG_MODE1;
	uint8_t *rcv = new uint8_t[2];
	_twi->transfert(_address, &cmd, 1, rcv, 2);
	_mode1 = rcv[0];
	_mode2 = rcv[1];
	delete[] rcv;
}

void PCA9685::setModes()
{
	uint8_t *cmd = new uint8_t[3];
	cmd[0] = REG_MODE1;
	cmd[1] = _mode1;
	cmd[2] = _mode2;
	_twi->set(_address, cmd, 3);
	delete[] cmd;
}
