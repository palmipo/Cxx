#include "mfrc522.h"
#include "ctrlspi.h"
#include "pia.h"
#include "tempo.h"

MFRC522::MFRC522(CtrlSPI * ctrl, PIA * irq, PIA * rst)
: DeviceSPI()
, _spi(ctrl)
, _irq_gpio(irq)
, _rst_gpio(rst)
{
	if (_rst_gpio)
	{
		_rst_gpio->write(1);
	}
}

MFRC522::~MFRC522()
{}

void MFRC522::init()
{
	if (_rst_gpio)
	{
		_rst_gpio->write(0);
		Tempo::millisecondes(2);
		_rst_gpio->write(1);
	}
	else
	{
		softReset();
	}

	setTxModeReg(0x00);
	setRxModeReg(0x00);

	setModWidthReg(0x26);

	setTModeReg(0x80);
	setTPrescalerReg(0xA9);
	setTReloadReg(0x03E8);

	setTxASKReg(0x40);
	setModeReg(0x3D);
}

void MFRC522::softReset()
{
	uint8_t RcvOff=1, PowerDown=1, Command=CommandReg_softReset;
	setCommandReg(RcvOff, PowerDown, Command);
	
	commandReg(&RcvOff, &PowerDown, &Command);
	while (PowerDown)
	{
		Tempo::millisecondes (500);
		commandReg(&RcvOff, &PowerDown, &Command);
	}
}

uint8_t MFRC522::readRegister (uint8_t addr)
{
	int32_t length = 2;
	uint8_t cmd[] = { (((addr << 1) & 0x7e) | 0x80), 0 };
	uint8_t data[ length ];
	_spi->transfer(cmd, data, length);
	return data[1];
}

void MFRC522::writeRegister (uint8_t addr, uint8_t val)
{
	int32_t length = 2;
	uint8_t cmd[] = { ((addr << 1) & 0x7e), val };
	uint8_t data[ length ];
	_spi->transfer(cmd, data, length);
}

//01h CommandReg starts and stops command execution Table 23 on page 38
void MFRC522::setCommandReg(uint8_t RcvOff, uint8_t PowerDown, uint8_t Command)
{
	// starts and stops command execution

	uint8_t res = 0;
	//~ 5 RcvOff 1 analog part of the receiver is switched off
	res |= (RcvOff & 1) << 5;
	//~ 4 PowerDown
	//~ 1 Soft power-down mode entered
	//~ 0 MFRC522 starts the wake up procedure during which this bit is 
	//~ read as a logic 1; it is read as a logic 0 when the MFRC522 is 
	//~ ready; see Section 8.6.2 on page 33
	//~ Remark: The PowerDown bit cannot be set when the SoftReset 
	//~ command is activated
	res |= (PowerDown & 1) << 4;
	//~ 3 to 0 Command[3:0] - activates a command based on the Command value; reading this register show
	res |= (Command & 0xF);

	writeRegister (0x01, res);
}

void MFRC522::commandReg(uint8_t * RcvOff, uint8_t * PowerDown, uint8_t * Command)
{
	// starts and stops command execution

	uint8_t res = readRegister (0x01);

	//~ 5 RcvOff 1 analog part of the receiver is switched off
	*RcvOff = (res & (1 << 5)) ? 1 : 0;
	//~ 4 PowerDown
	//~ 1 Soft power-down mode entered
	//~ 0 MFRC522 starts the wake up procedure during which this bit is 
	//~ read as a logic 1; it is read as a logic 0 when the MFRC522 is 
	//~ ready; see Section 8.6.2 on page 33
	//~ Remark: The PowerDown bit cannot be set when the SoftReset 
	//~ command is activated
	*PowerDown = (res & (1 << 4)) ? 1 : 0;
	//~ 3 to 0 Command[3:0] - activates a command based on the Command value; reading this register show
	*Command = res & 0xF;
}

//02h ComlEnReg enable and disable interrupt request control bits Table 25 on page 38
uint8_t MFRC522::setComlEnReg(uint8_t IRqInv, uint8_t TxIEn, uint8_t RxIEn, uint8_t IdleIEn, uint8_t HiAlertIEn, uint8_t LoAlertIEn, uint8_t ErrIEn, uint8_t TimerIEn)
{
	//  enable and disable interrupt request control bits

	uint8_t res = 0;
	//~ 7 IRqInv 1 signal on pin IRQ is inverted with respect to the Status1Reg register’s IRq bit
	//~ 0 signal on pin IRQ is equal to the IRq bit; in combination with the 
	//~ DivIEnReg register’s IRqPushPull bit, the default value of logic 1 ensures 
	//~ that the output level on pin IRQ is 3-state
	res |= (IRqInv & 1) << 7;
	//~ 6 TxIEn - allows the transmitter interrupt request (TxIRq bit) to be propagated to pin IRQ
	res |= (TxIEn & 1) << 6;
	//~ 5 RxIEn - allows the receiver interrupt request (RxIRq bit) to be propagated to pin  IRQ
	res |= (RxIEn & 1) << 5;
	//~ 4 IdleIEn - allows the idle interrupt request (IdleIRq bit) to be propagated to pin IRQ
	res |= (IdleIEn & 1) << 4;
	//~ 3 HiAlertIEn - allows the high alert interrupt request (HiAlertIRq bit) to be propagated to  pin IRQ
	res |= (HiAlertIEn & 1) << 3;
	//~ 2 LoAlertIEn - allows the low alert interrupt request (LoAlertIRq bit) to be propagated to  pin IRQ
	res |= (LoAlertIEn & 1) << 2;
	//~ 1 ErrIEn - allows the error interrupt request (ErrIRq bit) to be propagated to pin IRQ
	res |= (ErrIEn & 1) << 1;
	//~ 0 TimerIEn - allows the timer interrupt request (TimerIRq bit) to be propagated to pin  IRQ
	res |= (TimerIEn & 1);

	writeRegister (0x02, res);
	return res;
}

//03h DivlEnReg enable and disable interrupt request control bits Table 27 on page 39
uint8_t MFRC522::setDivlEnReg(uint8_t IRQPushPull, uint8_t MfinActIEn, uint8_t CRCIEn)
{
	//  enable and disable interrupt request control bits

	uint8_t res = 0;
	//~ 7 IRQPushPull
	//~ 1 pin IRQ is a standard CMOS output pin
	//~ 0 pin IRQ is an open-drain output pin
	res |= (IRQPushPull & 1) << 7;
	//~ 4 MfinActIEn - allows the MFIN active interrupt request to be propagated to pin IRQ
	res |= (MfinActIEn & 1) << 4;
	//~ 2 CRCIEn - allows the CRC interrupt request, indicated by the DivIrqReg register’s CRCIRq bit, to be propagated to pin IRQ
	res |= (CRCIEn & 1) << 2;

	writeRegister (0x03, res);
	return res;
}

//04h ComIrqReg interrupt request bits Table 29 on page 39
uint8_t MFRC522::setComIrqReg(uint8_t Set1, uint8_t TxIRq, uint8_t RxIRq, uint8_t IdleIRq, uint8_t HiAlertIRq, uint8_t LoAlertIRq, uint8_t ErrIRq, uint8_t TimerIRq)
{
	//  interrupt request bits Table 29 on page 39

	uint8_t res = 0;
	//~ 7 Set1
	//~ 1 indicates that the marked bits in the ComIrqReg register are set
	//~ 0 indicates that the marked bits in the ComIrqReg register are cleared
	res |= (Set1 & 1) << 7;
	//~ 6 TxIRq 1 set immediately after the last bit of the transmitted data was sent out
	res |= (TxIRq & 1) << 6;
	//~ 5 RxIRq 1 receiver has detected the end of a valid data stream
	//~ if the RxModeReg register’s RxNoErr bit is set to logic 1, the RxIRq bit is 
	//~ only set to logic 1 when data bytes are available in the FIFO
	res |= (RxIRq & 1) << 5;
	//~ 4 IdleIRq 1 If a command terminates, for example, when the CommandReg changes 
	//~ its value from any command to the Idle command (see Table 149 on 
	//~ page 70)
	//~ if an unknown command is started, the CommandReg register 
	//~ Command[3:0] value changes to the idle state and the IdleIRq bit is set
	//~ The microcontroller starting the Idle command does not set the IdleIRq 
	//~ bit
	res |= (IdleIRq & 1) << 4;
	//~ 3 HiAlertIRq 1 the Status1Reg register’s HiAlert bit is set
	//~ in opposition to the HiAlert bit, the HiAlertIRq bit stores this event and 
	//~ can only be reset as indicated by the Set1 bit in this register
	res |= (HiAlertIRq & 1) << 3;
	//~ 2 LoAlertIRq 1 Status1Reg register’s LoAlert bit is set
	//~ in opposition to the LoAlert bit, the LoAlertIRq bit stores this event and 
	//~ can only be reset as indicated by the Set1 bit in this register
	res |= (LoAlertIRq & 1) << 2;
	//~ 1 ErrIRq 1 any error bit in the ErrorReg register is set
	res |= (ErrIRq & 1) << 1;
	//~ 0 TimerIRq 1 the timer decrements the timer value in register TCounterValReg to zero
	res |= (TimerIRq & 1);

	return res;
}

//05h DivIrqReg interrupt request bits Table 31 on page 40
uint8_t MFRC522::setDivIrqReg(uint8_t Set2, uint8_t MfinActIRq, uint8_t CRCIRq)
{
	//  interrupt request bits Table 31 on page 40

	uint8_t res = 0;
	//~ 7 Set2
	//~ 1 indicates that the marked bits in the DivIrqReg register are set
	//~ 0 indicates that the marked bits in the DivIrqReg register are cleared
	res |= (Set2 & 1) << 7;
	//~ 4 MfinActIRq 1 MFIN is active
	//~ this interrupt is set when either a rising or falling signal edge is 
	//~ detected
	res |= (MfinActIRq & 1) << 4;
	//~ 2 CRCIRq 1 the CalcCRC command is active and all data is processed
	res |= (CRCIRq & 1) << 2;

	return res;
}

//06h ErrorReg error bits showing the error status of the last command executed Table 33 on page 41
uint8_t MFRC522::ErrorReg(uint8_t WrErr, uint8_t TempErr, uint8_t BufferOvfl, uint8_t CollErr, uint8_t CRCErr, uint8_t ParityErr, uint8_t ProtocolErr)
{
	//  error bits showing the error status of the last command executed Table 33 on page 41

	uint8_t res = 0;
	//~ 7 WrErr
	//~ 1 data is written into the FIFO buffer by the host during the MFAuthent 
	//~ command or if data is written into the FIFO buffer by the host during the 
	//~ time between sending the last bit on the RF interface and receiving the 
	//~ last bit on the RF interface
	res |= (WrErr & 1) << 7;
	//~ 6 TempErr[1] 1 internal temperature sensor detects overheating, in which case the 
	//~ antenna drivers are automatically switched off
	res |= (TempErr & 1) << 6;
	//~ 4 BufferOvfl 1 the host or a MFRC522’s internal state machine (e.g. receiver) tries to 
	//~ write data to the FIFO buffer even though it is already full
	res |= (BufferOvfl & 1) << 4;
	//~ 3 CollErr 1 a bit-collision is detected
	//~ cleared automatically at receiver start-up phase
	//~ only valid during the bitwise anticollision at 106 kBd
	//~ always set to logic 0 during communication protocols at 212 kBd, 
	//~ 424 kBd and 848 kBd
	res |= (CollErr & 1) << 3;
	//~ 2 CRCErr 1 the RxModeReg register’s RxCRCEn bit is set and the CRC calculation 
	//~ fails
	//~ automatically cleared to logic 0 during receiver start-up phase
	res |= (CRCErr & 1) << 2;
	//~ 1 ParityErr 1 parity check failed
	//~ automatically cleared during receiver start-up phase
	//~ only valid for ISO/IEC 14443 A/MIFARE communication at 106 kBd
	res |= (ParityErr & 1) << 1;
	//~ 0 ProtocolErr 1 set to logic 1 if the SOF is incorrect
	//~ automatically cleared during receiver start-up phase
	//~ bit is only valid for 106 kBd
	//~ during the MFAuthent command, the ProtocolErr bit is set to logic 1 if the 
	//~ number of bytes received in one data stream is incorrect
	res |= (ProtocolErr & 1);

	return res;
}

//07h Status1Reg communication status bits Table 35 on page 42
uint8_t MFRC522::Status1Reg(uint8_t CRCOk, uint8_t CRCReady, uint8_t IRq, uint8_t TRunning, uint8_t HiAlert, uint8_t LoAlert)
{
	//  communication status bits Table 35 on page 42

	uint8_t res = 0;
	//~ 6 CRCOk 1 the CRC result is zero
	//~ for data transmission and reception, the CRCOk bit is undefined: use the 
	//~ ErrorReg register’s CRCErr bit
	//~ indicates the status of the CRC coprocessor, during calculation the value 
	//~ changes to logic 0, when the calculation is done correctly the value 
	//~ changes to logic 1
	res |= (CRCOk & 1) << 6;
	//~ 5 CRCReady 1 the CRC calculation has finished
	//~ only valid for the CRC coprocessor calculation using the CalcCRC 
	//~ command
	res |= (CRCReady & 1) << 5;
	//~ 4 IRq - indicates if any interrupt source requests attention with respect to the 
	//~ setting of the interrupt enable bits: see the ComIEnReg and DivIEnReg 
	//~ registers
	res |= (IRq & 1) << 4;
	//~ 3 TRunning 1 MFRC522’s timer unit is running, i.e. the timer will decrement the 
	//~ TCounterValReg register with the next timer clock
	//~ Remark: in gated mode, the TRunning bit is set to logic 1 when the 
	//~ timer is enabled by TModeReg register’s TGated[1:0] bits; this bit is not 
	//~ influenced by the gated signal
	res |= (TRunning & 1) << 3;
	//~ 1 HiAlert 1 the number of bytes stored in the FIFO buffer corresponds to equation: 
	//~ example:
	//~ FIFO length = 60, WaterLevel = 4 ? HiAlert = 1
	//~ FIFO length = 59, WaterLevel = 4 ? HiAlert = 0
	res |= (HiAlert & 1) << 1;
	//~ 0 LoAlert 1 the number of bytes stored in the FIFO buffer corresponds to equation:
	//~ example:
	//~ FIFO length = 4, WaterLevel = 4 ? LoAlert = 1
	//~ FIFO length = 5, WaterLevel = 4 ? LoAlert = 0
	res |= (LoAlert & 1);

	return res;
}

//08h Status2Reg receiver and transmitter status bits Table 37 on page 43
uint8_t MFRC522::Status2Reg(uint8_t TempSensClear, uint8_t I2CForceHS, uint8_t MFCrypto1On, uint8_t ModemState)
{
	//  receiver and transmitter status bits Table 37 on page 43

	uint8_t res = 0;
	//~ 7 TempSensClear 1 clears the temperature error if the temperature is below the alarm limit of 125 ?C
	res |= (TempSensClear & 1) << 1;
	//~ 6 I2CForceHS I2C-bus input filter settings:
	//~ 1 the I2C-bus input filter is set to the High-speed mode independent of the I2C-bus protocol
	//~ 0 the I2C-bus input filter is set to the I2C-bus protocol used
	res |= (I2CForceHS & 1) << 1;
	//~ 3 MFCrypto1On - indicates that the MIFARE Crypto1 unit is switched on and 
	//~ therefore all data communication with the card is encrypted
	//~ can only be set to logic 1 by a successful execution of the MFAuthent command
	//~ only valid in Read/Write mode for MIFARE standard cards this bit is cleared by software
	res |= (MFCrypto1On & 1) << 1;
	//~ 2 to 0 ModemState[2:0] - shows the state of the transmitter and receiver state machines:
		//~ 000 idle
		//~ 001 wait for the BitFramingReg register’s StartSend bit
		//~ 010 TxWait: wait until RF field is present if the TModeReg 
		//~ register’s TxWaitRF bit is set to logic 1
		//~ the minimum time for TxWait is defined by the TxWaitReg register
		//~ 011 transmitting
		//~ 100 RxWait: wait until RF field is present if the TModeReg 
		//~ register’s TxWaitRF bit is set to logic 1
		//~ the minimum time for RxWait is defined by the RxWaitReg register
		//~ 101 wait for data
		//~ 110 receiving
	res |= (ModemState & 7);

	return res;
}

//09h FIFODataReg input and output of 64 byte FIFO buffer Table 39 on page 44
uint8_t MFRC522::FIFODataReg ()
{
	// input and output of 64 byte FIFO buffer Table 39 on page 44

	uint8_t res = 0;
	//~ 7 to 0 FIFOData[7:0] data input and output port for the internal 64-byte FIFO buffer
	//~ FIFO buffer acts as parallel in/parallel out converter for all serial data 
	//~ stream inputs and outputs
	return res;
}

//0Ah FIFOLevelReg number of bytes stored in the FIFO buffer Table 41 on page 44
uint8_t MFRC522::FIFOLevelReg ()
{
	// number of bytes stored in the FIFO buffer Table 41 on page 44

	uint8_t res = 0;
	//~ 7 FlushBuffer 1 immediately clears the internal FIFO buffer’s read and write pointer 
	//~ and ErrorReg register’s BufferOvfl bit reading this bit always returns 0
	//~ 6 to 0 FIFOLevel[6:0]
	//~ - indicates the number of bytes stored in the FIFO buffer
	//~ writing to the FIFODataReg registe
	return res;
}

//0Bh WaterLevelReg level for FIFO underflow and overflow warning Table 43 on page 44
uint8_t MFRC522::WaterLevelReg ()
{
	// level for FIFO underflow and overflow warning Table 43 on page 44

	uint8_t res = 0;
	//~ 7 to 6 reserved reserved for future use
	//~ 5 to 0 WaterLevel[5:0]
	//~ defines a warning level to indicate a FIFO buffer overflow or underflow:
	//~ Status1Reg register’s HiAlert bit is set to logic 1 if the remaining 
	//~ number of bytes in the FIFO buffer space is equal to, or less than the 
	//~ defined number of WaterLevel bytes
	//~ Status1Reg register’s LoAlert bit is set to logic 1 if equal to, or less 
	//~ than the WaterLevel bytes in the FIFO buffer
	//~ Remark: to calculate values for HiAlert and LoAlert see 
	//~ Section 9.3.1.8 on page 42
	return res;
}

//0Ch ControlReg miscellaneous control registers Table 45 on page 45
uint8_t MFRC522::ControlReg ()
{
	// miscellaneous control registers Table 45 on page 45

	uint8_t res = 0;
	//~ 7 TStopNow 1 timer stops immediately reading this bit always returns it to logic0
	//~ 6 TStartNow 1 timer starts immediately reading this bit always returns it to logic 0
	//~ 2 to 0 RxLastBits[2:0] - indicates the number of valid bits in the last received byte
	//~ if this value is 000b, the whole byte is valid

	return res;
}

//0Dh BitFramingReg adjustments for bit-oriented frames Table 47 on page 46
uint8_t MFRC522::BitFramingReg ()
{
	// adjustments for bit-oriented frames Table 47 on page 46

	uint8_t res = 0;
	//~ 7 StartSend 1 starts the transmission of data only valid in combination with the Transceive command
	//~ 6 to 4 RxAlign[2:0] used for reception of bit-oriented frames: defines the bit 
	//~ position for the first bit received to be stored in the FIFO buffer example:
	//~ 0 LSB of the received bit is stored at bit position 0, the second received bit is stored at bit position 1
	//~ 1 LSB of the received bit is stored at bit position 1, the second received bit is stored at bit position 2
	//~ 7 LSB of the received bit is stored at bit position 7, the second received bit is stored in the next byte that follows at bit position 0
	//~ These bits are only to be used for bitwise anticollision at 106 kBd, for all other modes they are set to 0
	//~ 2 to 0 TxLastBits[2:0] - used for transmission of bit oriented frames: defines the number of bits of the last byte that will be transmitted
	//~ 000b indicates that all bits of the last byte will be transmitted
	return res;
}

//0Eh CollReg bit position of the first bit-collision detected on the RF interface Table 49 on page 46
uint8_t MFRC522::CollReg ()
{
	// bit position of the first bit-collision detected on the RF interface Table 49 on page 46

	uint8_t res = 0;
	//~ 7 ValuesAfterColl 0 all received bits will be cleared after a collision only used during bitwise anticollision at 106 kBd, otherwise it is set to logic 1
	//~ 5 CollPosNotValid 1 no collision detected or the position of the collision is out of the range of CollPos[4:0]
	//~ MFRC522 All information provided in this document is subject to legal disclaimers. © NXP Semiconductors N.V. 2016. All rights reserved.
	//~ 4 to 0 CollPos[4:0] - shows the bit position of the first detected collision in a received frame only data bits are interpreted example:
	//~ 00h indicates a bit-collision in the 32nd bit
	//~ 01h indicates a bit-collision in the 1st bit
	//~ 08h indicates a bit-collision in the 8th bit
	//~ These bits will only be interpreted if the 
	//~ CollPosNotValid bit is set to logic 0
	return res;
}

//11h ModeReg defines general modes for transmitting and receiving Table 55 on page 48
void MFRC522::setModeReg (uint8_t val)
{
	writeRegister(0x11, val);
}

uint8_t MFRC522::ModeReg ()
{
	// defines general modes for transmitting and receiving Table 55 on page 48

	uint8_t res = 0;
	//~ 7 MSBFirst 1 CRC coprocessor calculates the CRC with MSB first in the CRCResultReg register the values for the CRCResultMSB[7:0] bits and the CRCResultLSB[7:0] bits are bit reversed
	//~ Remark: during RF communication this bit is ignored
	//~ 5 TxWaitRF 1 transmitter can only be started if an RF field is generated
	//~ 3 PolMFin defines the polarity of pin MFIN
	//~ Remark: the internal envelope signal is encoded active LOW, changing this bit generates a MFinActIRq event
	//~ 1 polarity of pin MFIN is active HIGH
	//~ 0 polarity of pin MFIN is active LOW
	//~ 1 to 0 CRCPreset[1:0]defines the preset value for the CRC coprocessor for the CalcCRC command
	//~ Remark: during any communication, the preset values are selected automatically according to the definition of bits in the 
	//~ RxModeReg and TxModeReg registers
	//~ 00 0000h
	//~ 01 6363h
	//~ 10 A671h
	//~ 11 FFFFh
	return res;
}

//12h TxModeReg defines transmission data rate and framing Table 57 on page 48
void MFRC522::setTxModeReg (uint8_t val)
{
	writeRegister(0x12, val);
}

uint8_t MFRC522::TxModeReg ()
{
	// defines transmission data rate and framing Table 57 on page 48

	uint8_t res = 0;
	//~ 7 TxCRCEn 1 enables CRC generation during data transmission
	//~ Remark: can only be set to logic 0 at 106 kBd
	//~ 6 to 4 TxSpeed[2:0] defines the bit rate during data transmission the MFRC522 handles transfer speeds up to 
	//~ 848 kBd
	//~ 000 106 kBd
	//~ 001 212 kBd
	//~ 010 424 kBd
	//~ 011 848 kBd
	//~ 100 reserved
	//~ 101 reserved
	//~ 110 reserved
	//~ 111 reserved
	//~ 3 InvMod 1 modulation of transmitted data is inverted
	return res;
}

//13h RxModeReg defines reception data rate and framing Table 59 on page 49
void MFRC522::setRxModeReg (uint8_t val)
{
	writeRegister(0x13, val);
}

uint8_t MFRC522::RxModeReg ()
{
	// defines reception data rate and framing Table 59 on page 49

	uint8_t res = 0;
	//~ 7 RxCRCEn 1 enables the CRC calculation during reception
	//~ Remark: can only be set to logic 0 at 106 kBd
	//~ 6 to 4 RxSpeed[2:0] defines the bit rate while receiving data
	//~ the MFRC522 handles transfer speeds up to 848 kBd
	//~ 000 106 kBd
	//~ 001 212 kBd
	//~ 010 424 kBd
	//~ 011 848 kBd
	//~ 100 reserved
	//~ 101 reserved
	//~ 110 reserved
	//~ 111 reserved
	//~ 3 RxNoErr 1 an invalid received data stream (less than 4 bits received) will 
	//~ be ignored and the receiver remains active
	//~ 2 RxMultiple 0 receiver is deactivated after receiving a data frame
	//~ 1 able to receive more than one data frame
	//~ only valid for data rates above 106 kBd in order to handle the 
	//~ polling command
	//~ after setting this bit the Receive and Transceive commands will 
	//~ not terminate automatically. Multiple reception can only be 
	//~ deactivated by writing any command (except the Receive 
	//~ command) to the CommandReg register, or by the host clearing 
	//~ the bit
	//~ if set to logic 1, an error byte is added to the FIFO buffer at the 
	//~ end of a received data stream which is a copy of the ErrorReg 
	//~ register value. For the MFRC522 version 2.0 the CRC status is 
	//~ reflected in the signal CRCOk, which indicates the actual status 
	//~ of the CRC coprocessor. For the MFRC522 version 1.0 the CRC 
	//~ status is reflected in the signal CRCErr.
	//~ 1 to 0 reserved - reserved for future us
	return res;
}

//14h TxControlReg controls the logical behavior of the antenna driver pins TX1 and TX2 Table 61 on page 50
uint8_t MFRC522::TxControlReg ()
{
	// controls the logical behavior of the antenna driver pins TX1 and TX2 Table 61 on page 50

	uint8_t res = 0;
	//~ 7 InvTx2RFOn 1 output signal on pin TX2 inverted when driver TX2 is enabled
	//~ 6 InvTx1RFOn 1 output signal on pin TX1 inverted when driver TX1 is enabled
	//~ 5 InvTx2RFOff 1 output signal on pin TX2 inverted when driver TX2 is disabled
	//~ 4 InvTx1RFOff 1 output signal on pin TX1 inverted when driver TX1 is disabled
	//~ 3 Tx2CW 1 output signal on pin TX2 continuously delivers the unmodulated 13.56 MHz energy carrier
		//~ 0 Tx2CW bit is enabled to modulate the 13.56 MHz energy carrier
	//~ 1 Tx2RFEn 1 output signal on pin TX2 delivers the 13.56 MHz energy carrier modulated by the transmission data
	//~ 0 Tx1RFEn 1 output signal on pin TX1 delivers the 13.56 MHz energy carrier modulated by the transmission data

	return res;
}

//15h TxASKReg controls the setting of the transmission modulation Table 63 on page 51
void MFRC522::setTxASKReg (uint8_t val)
{
	writeRegister(0x15, val);
}

uint8_t MFRC522::TxASKReg ()
{
	// controls the setting of the transmission modulation Table 63 on page 51

	uint8_t res = 0;
	//~ 7 reserved - reserved for future use
	//~ 6 Force100ASK 1 forces a 100 % ASK modulation independent of the ModGsPReg register setting
	//~ 5 to 0 reserved - reserved for future use
	return res;
}

//16h TxSelReg selects the internal sources for the antenna driver Table 65 on page 51
uint8_t MFRC522::TxSelReg ()
{
	// selects the internal sources for the antenna driver Table 65 on page 51

	uint8_t res = 0;
	//~ 7 to 6 reserved - reserved for future use
	//~ 5 to 4 DriverSel[1:0]- selects the input of drivers TX1 and TX2
	//~ 00 3-state; in soft power-down the drivers are only in 3-state mode if the DriverSel[1:0] value is set to 3-state mode
	//~ 01 modulation signal (envelope) from the internal encoder, Miller pulse encoded
	//~ 10 modulation signal (envelope) from pin MFIN
	//~ 11 HIGH; the HIGH level depends on the setting of bits InvTx1RFOn/InvTx1RFOff and InvTx2RFOn/InvTx2RFOff
	//~ 3 to 0 MFOutSel[3:0]selects the input for pin MFOUT
	//~ 0000 3-state
	//~ 0001 LOW
	//~ 0010 HIGH
	//~ 0011 test bus signal as defined by the TestSel1Reg register’s TstBusBitSel[2:0] value
	//~ 0100 modulation signal (envelope) from the internal encoder, Miller pulse encoded
	//~ 0101 serial data stream to be transmitted, data stream before Miller encoder
	//~ 0110 reserved
	//~ 0111 serial data stream received, data stream after Manchester decoder
	//~ 1000 to 1111 reserved
	return res;
}

//17h RxSelReg selects internal receiver settings Table 67 on page 52
uint8_t MFRC522::RxSelReg ()
{
	// selects internal receiver settings Table 67 on page 52

	uint8_t res = 0;
	//~ 7 to 6 UARTSel[1:0]selects the input of the contactless UART
	//~ 00 constant LOW
	//~ 01 Manchester with subcarrier from pin MFIN
	//~ 10 modulated signal from the internal analog module, default
	//~ 11 NRZ coding without subcarrier from pin MFIN which is only valid 
	//~ for transfer speeds above 106 kBd
	//~ 5 to 0 RxWait[5:0]- after data transmission the activation of the receiver is delayed for RxWait bit-clocks, during this ‘frame guard time’ any signal on pin RX is ignored
	//~ this parameter is ignored by the Receive command
	//~ all other commands, such as Transceive, MFAuthent use this parameter
	//~ the counter starts immediately after the external RF field is switched on

	return res;
}

//18h RxThresholdReg selects thresholds for the bit decoder Table 69 on page 53
uint8_t MFRC522::RxThresholdReg ()
{
	// selects thresholds for the bit decoder Table 69 on page 53

	uint8_t res = 0;
	//~ 7 to 4 MinLevel[3:0]defines the minimum signal strength at the decoder input that will be accepted if the signal strength is below this level it is not evaluated
	//~ 2 to 0 CollLevel[2:0]defines the minimum signal strength at the decoder input that must be reached by the weaker half-bit of the Manchester encoded signal to generate a bit-collision relative to the amplitude of the stronger half-bit
	return res;
}

//19h DemodReg defines demodulator settings Table 71 on page 53
uint8_t MFRC522::DemodReg ()
{
	// defines demodulator settings Table 71 on page 53

	uint8_t res = 0;
	//~ 7 to 6 AddIQ[1:0]- defines the use of I and Q channel during reception
	//~ Remark: the FixIQ bit must be set to logic 0 to enable the following settings:
	//~ 00 selects the stronger channel
	//~ 01 selects the stronger channel and freezes the selected channel during communication
	//~ 10 reserved
	//~ 11 reserved
	//~ 5 FixIQ 1 if AddIQ[1:0] are set to X0b, the reception is fixed to I channel 
	//~ if AddIQ[1:0] are set to X1b, the reception is fixed to Q channel
	//~ 4 TPrescalEven R/W Available on RC522 version 1.0 and version 2.0:
	//~ If set to logic 0 the following formula is used to calculate the timer frequency of the prescaler:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+1).
	//~ Only available on version 2.0:
	//~ If set to logic 1 the following formula is used to calculate the timer frequency of the prescaler:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+2).
	//~ Default TPrescalEven bit is logic 0, find more information on the prescaler in Section 8.5.
	//~ 3 to 2 TauRcv[1:0] - changes the time-constant of the internal PLL during data reception
	//~ Remark: if set to 00b the PLL is frozen during data reception
	//~ 1 to 0 TauSync[1:0] - changes the time-constant of the internal PLL during burst
	return res;
}

//1Ch MfTxReg controls some MIFARE communication transmit parameters Table 77 on page 55
uint8_t MFRC522::MfTxReg ()
{
	// controls some MIFARE communication transmit parameters Table 77 on page 55

	uint8_t res = 0;
	//~ 1 to 0 TxWait defines the additional response time
	//~ 7 bits are added to the value of the register bit by default
	return res;
}

//1Dh MfRxReg controls some MIFARE communication receive parameters Table 79 on page 55
uint8_t MFRC522::MfRxReg ()
{
	// controls some MIFARE communication receive parameters Table 79 on page 55

	uint8_t res = 0;
	//~ 4 ParityDisable 1 generation of the parity bit for transmission and the parity check for receiving is switched off
	//~ the received parity bit is handled like a data bit
	return res;
}

//1Fh SerialSpeedReg selects the speed of the serial UART interface Table 83 on page 55
uint8_t MFRC522::SerialSpeedReg ()
{
	// selects the speed of the serial UART interface Table 83 on page 55

	uint8_t res = 0;
	//~ 7 to 5 BR_T0[2:0] factor BR_T0 adjusts the transfer speed: for description, see Section 8.1.3.2 on page 12
	//~ 4 to 0 BR_T1[4:0] factor BR_T1 adjusts the transfer speed: for description, see Section 8.1.3.2 on page 12

	return res;
}

//21h CRCResultReg shows the MSB and LSB values of the CRC calculation Table 87 on page 57
uint8_t MFRC522::CRCResultReg ()
{
	// shows the MSB and LSB values of the CRC calculation Table 87 on page 57

	uint8_t res = 0;
	//~ 7 to 0 CRCResultMSB[7:0]shows the value of the CRCResultReg register’s most significant byte
	//~ only valid if Status1Reg register’s CRCReady bit is set to logic 1
	return res;
}

//24h ModWidthReg controls the ModWidth setting Table 93 on page 58
void MFRC522::setModWidthReg (uint8_t val)
{
	writeRegister(0x24, val);
}

uint8_t MFRC522::ModWidthReg ()
{
	// controls the ModWidth setting Table 93 on page 58

	uint8_t res = 0;
	//~ 7 to 0 CRCResultLSB[7:0]shows the value of the least significant byte of the CRCResultReg register
	//~ only valid if Status1Reg register’s CRCReady bit is set to logic 1

	return res;
}

//26h RFCfgReg configures the receiver gain Table 97 on page 59
uint8_t MFRC522::RFCfgReg ()
{
	// configures the receiver gain Table 97 on page 59

	uint8_t res = 0;
	//~ 7 to 0 ModWidth[7:0] defines the width of the Miller modulation as multiples of the carrier frequency (ModWidth + 1 / fclk)
	//~ the maximum value is half the bit period
	return res;
}

//27h GsNReg selects the conductance of the antenna driver pins TX1 and TX2 for modulation Table 99 on page 59
uint8_t MFRC522::GsNReg ()
{
	// selects the conductance of the antenna driver pins TX1 and TX2 for modulation Table 99 on page 59

	uint8_t res = 0;
	//~ 6 to 4 RxGain[2:0]defines the receiver’s signal voltage gain factor:
	//~ 000 18 dB
	//~ 001 23 dB
	//~ 010 18 dB
	//~ 011 23 dB
	//~ 100 33 dB
	//~ 101 38 dB
	//~ 110 43 dB
	//~ 111 48 dB
	return res;
}

//28h CWGsPReg defines the conductance of the p-driver output during periods of no modulation Table 101 on page 60
uint8_t MFRC522::CWGsPReg ()
{
	// defines the conductance of the p-driver output during periods of no modulation Table 101 on page 60

	uint8_t res = 0;
	//~ 7 to 4 CWGsN[3:0]defines the conductance of the output n-driver during periods without modulation which can be used to regulate the output power and subsequently current consumption and operating distance
	//~ Remark: the conductance value is binary-weighted
	//~ during soft Power-down mode the highest bit is forced to logic 1
	//~ value is only used if driver TX1 or TX2 is switched on
	//~ 3 to 0 ModGsN[3:0]defines the conductance of the output n-driver during periods without modulation which can be used to regulate the modulation index
	//~ Remark: the conductance value is binary weighted
	//~ during soft Power-down mode the highest bit is forced to logic 1
	//~ value is only used if driver TX1 or TX2 is switched on

	return res;
}

//29h ModGsPReg defines the conductance of the p-driver output during periods of modulation Table 103 on page 60
uint8_t MFRC522::ModGsPReg ()
{
	// defines the conductance of the p-driver output during periods of modulation Table 103 on page 60

	uint8_t res = 0;
	//~ 5 to 0 ModGsP[5:0] defines the conductance of the p-driver output during modulation which can be used to regulate the modulation index
	//~ Remark: the conductance value is binary weighted
	//~ during soft Power-down mode the highest bit is forced to logic 1
	//~ if the TxASKReg register’s Force100ASK bit is set to logic 1 the value of ModGsP has no effect
	return res;
}

//2Ah TModeReg defines settings for the internal timer Table 105 on page 60
void MFRC522::setTModeReg(uint8_t val)
{
	writeRegister(0x2A, val);
}

uint8_t MFRC522::TModeReg ()
{
	// defines settings for the internal timer Table 105 on page 60

	uint8_t res = 0;
	//~ 7 TAuto 1 timer starts automatically at the end of the transmission in all communication modes at all speeds
	//~ if the RxModeReg register’s RxMultiple bit is not set, the timer stops immediately after receiving the 5th bit (1 start bit, 4 data bits)
	//~ if the RxMultiple bit is set to logic 1 the timer never stops, in which case the timer can be stopped by setting the ControlReg register’s TStopNow bit to logic 1
	//~ 0 indicates that the timer is not influenced by the protocol
	//~ 6 to 5 TGated[1:0] internal timer is running in gated mode
	//~ Remark: in gated mode, the Status1Reg register’s TRunning bit is logic 1 when the timer is enabled by the TModeReg register’s TGated[1:0] bits
	//~ this bit does not influence the gating signal
	//~ 00 non-gated mode
	//~ 01 gated by pin MFIN
	//~ 10 gated by pin AUX1
	//~ 11 -
	//~ 4 TAutoRestart 1 timer automatically restarts its count-down from the 16-bit timer reload value instead of counting down to zero
	//~ 0 timer decrements to 0 and the ComIrqReg register’s TimerIRq bit is set to logic 1
	//~ 3 to 0 TPrescaler_Hi[3:0] - defines the higher 4 bits of the TPrescaler value
	//~ The following formula is used to calculate the timer frequency if the DemodReg register’s TPrescalEven bit in Demot Regis set to logic 0:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+1).
	//~ Where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo] (TPrescaler value on 12 bits) (Default TPrescalEven bit is logic 0)
	//~ The following formula is used to calculate the timer frequency if the DemodReg register’s TPrescalEven bit is set to logic 1:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+2).
	//~ See Section 8.5 “Timer unit”
	return res;
}

//2Bh TPrescalerReg Table 107 on page 61
void MFRC522::setTPrescalerReg(uint8_t val)
{
	writeRegister(0x28, val);
}

uint8_t MFRC522::TPrescalerReg ()
{
	// Table 107 on page 61

	uint8_t res = 0;
	//~ 7 to 0 TPrescaler_Lo[7:0] defines the lower 8 bits of the TPrescaler value
	//~ The following formula is used to calculate the timer frequency if the DemodReg register’s TPrescalEven bit is set to logic 0:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+1).
	//~ Where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo] (TPrescaler value on 12 bits) (Default TPrescalEven bit is logic 0)
	//~ The following formula is used to calculate the timer frequency if the DemodReg register’s TPrescalEven bit inDemoReg is set to logic 1:
	//~ ftimer = 13.56 MHz / (2*TPreScaler+2).
	//~ See Section 8.5 “Timer unit”
	return res;
}

//2Ch TReloadReg defines the 16-bit timer reload value Table 109 on page 62
void MFRC522::setTReloadReg(uint16_t val)
{
	uint8_t v[] = { ((val & 0xFF00) >> 8), (val & 0X00FF) };
	writeRegister(0x2C, v[0]);
	writeRegister(0x2D, v[1]);
}

uint16_t MFRC522::TReloadReg ()
{
	// defines the 16-bit timer reload value Table 109 on page 62

	uint16_t res = 0;
	//~ 7 to 0 TReloadVal_Hi[7:0] defines the higher 8 bits of the 16-bit timer reload value
	//~ on a start event, the timer loads the timer reload value
	//~ changing this register affects the timer only at the next start event

	//~ 7 to 0 TReloadVal_Lo[7:0] defines the lower 8 bits of the 16-bit timer reload value
	//~ on a start event, the timer loads the timer reload value
	//~ changing this register affects the timer only at the next start event
	return res;
}

//2Eh TCounterValReg shows the 16-bit timer value Table 113 on page 63
uint16_t MFRC522::TCounterValReg ()
{
	// shows the 16-bit timer value Table 113 on page 63

	uint16_t res = 0;
	//~ 7 to 0 TCounterVal_Hi[7:0] timer value higher 8 bits
	//~ 7 to 0 TCounterVal_Lo[7:0] timer value lower 8 bits
	return res;
}

//31h TestSel1Reg general test signal configuration Table 119 on page 63
uint8_t MFRC522::TestSel1Reg ()
{
	// general test signal configuration Table 119 on page 63

	uint8_t res = 0;
	//~ 2 to 0 TstBusBitSel[2:0]selects a test bus signal which is output at pin MFOUT
	//~ if AnalogSelAux2[3:0] = FFh in AnalogTestReg register, test bus signal is also output at pins AUX1 or AUX2
	return res;
}

//32h TestSel2Reg general test signal configuration and PRBS control Table 121 on page 64
uint8_t MFRC522::TestSel2Reg ()
{
	// general test signal configuration and PRBS control Table 121 on page 64

	uint8_t res = 0;
	//~ 7 TstBusFlip 1 test bus is mapped to the parallel port in the following order:
	//~ TstBusBit4,TstBusBit3, TstBusBit2, TstBusBit6, TstBusBit5, TstBusBit0; see Section 16.1 on page 82
	//~ 6 PRBS9 - starts and enables the PRBS9 sequence according to ITU-TO150
	//~ Remark: all relevant registers to transmit data must be configured before entering PRBS9 mode
	//~ the data transmission of the defined sequence is started by the Transmit command
	//~ 5 PRBS15 - starts and enables the PRBS15 sequence according to ITU-TO150
	//~ Remark: all relevant registers to transmit data must be configured before entering PRBS15 mode
	//~ the data transmission of the defined sequence is started by the Transmit command
	//~ 4 to 0 TestBusSel[4:0] - selects the test bus; see Section 16.1 “Test signals
	return res;
}

//33h TestPinEnReg enables pin output driver on pins D1 to D7 Table 123 on page 64
uint8_t MFRC522::TestPinEnReg ()
{
	// enables pin output driver on pins D1 to D7 Table 123 on page 64

	uint8_t res = 0;
	//~ 7 RS232LineEn 0 serial UART lines MX and DTRQ are disabled
	//~ 6 to 1 TestPinEn[5:0]- enables the output driver on one of the data pins D1 to D7 which outputs a test signal
	//~ Example:
	//~ setting bit 1 to logic 1 enables pin D1 output
	//~ setting bit 5 to logic 1 enables pin D5 output
	//~ Remark: If the SPI is used, only pins D1 to D4 can be used. If the serial UART interface is used and the RS232LineEn bit is set to logic 1 only pins D1 to D4 can be used.
	return res;
}

//34h TestPinValueReg defines the values for D1 to D7 when it is used as an I/O bus Table 125 on page 65
uint8_t MFRC522::TestPinValueReg()
{
	//  defines the values for D1 to D7 when it is used as an I/O bus Table 125 on page 65

	uint8_t res = 0;
	//~ 7 UseIO 1 enables the I/O functionality for the test port when one of the serial interfaces is used
	//~ the input/output behavior is defined by value TestPinEn[5:0] in the TestPinEnReg register
	//~ the value for the output behavior is defined by TestPinValue[5:0]
	//~ 6 to 1 TestPinValue[5:0]- defines the value of the test port when it is used as I/O and each output must be enabled by TestPinEn[5:0] in the TestPinEnReg register
	//~ Remark: Reading the register indicates the status of pins D6 to D1 if the UseIO bit is set to logic 1. If the UseIO bit is set to logic 0, the value of the TestPinValueReg register is read back.
	return res;
}

//35h TestBusReg shows the status of the internal test bus Table 127 on page 65
uint8_t MFRC522::TestBusReg()
{
	//  shows the status of the internal test bus Table 127 on page 65

	uint8_t res = 0;
	//~ 7 to 0 TestBus[7:0] shows the status of the internal test bus the test bus is selected using the TestSel2Reg register; see Section 16.1 on page 82
	return res;
}

//36h AutoTestReg controls the digital self test Table 129 on page 66
uint8_t MFRC522::AutoTestReg()
{
	//  controls the digital self test Table 129 on page 66

	uint8_t res = 0;
	//~ 6 AmpRcv 1 internal signal processing in the receiver chain is performed non-linearly which increases the operating distance in communication modes at 106 kBd
	//~ Remark: due to non-linearity, the effect of the RxThresholdReg register’s MinLevel[3:0] and the CollLevel[2:0] values is also non-linear
	//~ 3 to 0 SelfTest[3:0] - enables the digital self test
	//~ the self test can also be started by the CalcCRC command; see Section 10.3.1.4 on page 71
	//~ the self test is enabled by value 1001b
	//~ Remark: for default operation the self test must be disabled by value 0000b
	return res;
}

//37h VersionReg shows the software version Table 131 on page 66
uint8_t MFRC522::versionReg(uint8_t * chiptype, uint8_t * version)
{
	//  shows the software version Table 131 on page 66

	uint8_t res = readRegister (0x37);
	//~ 7 to 4 Chiptype ‘9’ stands for MFRC522
	*chiptype = ( res & 0xf0 ) >> 4;

	//~ 3 to 0 Version ‘1’ stands for MFRC522 version 1.0 and ‘2’ stands for MFRC522 version 2.0.
	*version = ( res & 0x0f );

	return 0;
}

//38h AnalogTestReg controls the pins AUX1 and AUX2 Table 133 on page 67
uint8_t MFRC522::AnalogTestReg()
{
	//  controls the pins AUX1 and AUX2 Table 133 on page 67

	uint8_t res = 0;
	//~ 7 to 4 AnalogSelAux1[3:0]controls pin AUX1
		//~ 0000 3-state
		//~ 0001 output of TestDAC1 (AUX1), output of TestDAC2 (AUX2)[1]
		//~ 0010 test signal Corr1[1]
		//~ 0011 reserved
		//~ 0100 DAC: test signal MinLevel[1]
		//~ 0101 DAC: test signal ADC_I[1]
		//~ 0110 DAC: test signal ADC_Q[1]
		//~ 0111 reserved
		//~ 1000 reserved, test signal for production test[1]
		//~ 1001 reserved
		//~ 1010 HIGH
		//~ 1011 LOW
		//~ 1100 TxActive:
			//~ at 106 kBd: HIGH during Start bit, Data bit, Parity and CRC
			//~ at 212 kBd: 424 kBd and 848 kBd: HIGH during data and CRC
		//~ 1101 RxActive:
			//~ at 106 kBd: HIGH during Data bit, Parity and CRC
			//~ at 212 kBd: 424 kBd and 848 kBd: HIGH during data and CRC
		//~ 1110 subcarrier detected:
			//~ 106 kBd: not applicable
			//~ 212 kBd: 424 kBd and 848 kBd: HIGH during last part of data and CRC
		//~ 1111 test bus bit as defined by the TestSel1Reg register’s 
	//~ TstBusBitSel[2:0] bits Remark: all test signals are described in Section 16.1 on page 82
	//~ 3 to 0 AnalogSelAux2[3:0]- controls pin AUX2 (see bit descriptions for AUX1)
	return res;
}

//39h TestDAC1Reg defines the test value for TestDAC1 Table 135 on page 68
uint8_t MFRC522::TestDAC1Reg()
{
	//  defines the test value for TestDAC1 Table 135 on page 68

	uint8_t res = 0;
	//~ 5 to 0 TestDAC1[5:0] defines the test value for TestDAC1
	//~ output of DAC1 can be routed to AUX1 by setting value AnalogSelAux1[3:0] to 0001b in the AnalogTestReg register
	return res;
}

//3Ah TestDAC2Reg defines the test value for TestDAC2 Table 137 on page 68
uint8_t MFRC522::TestDAC2Reg()
{
	//  defines the test value for TestDAC2 Table 137 on page 68

	uint8_t res = 0;
	//~ 5 to 0 TestDAC2[5:0] defines the test value for TestDAC2
	//~ output of DAC2 can be routed to AUX2 by setting value AnalogSelAux2[3:0] to 0001b in the AnalogTestReg register
	return res;
}

//3Bh TestADCReg shows the value of ADC I and Q channels Table 139 on page 68
uint8_t MFRC522::TestADCReg()
{
	//  shows the value of ADC I and Q channels Table 139 on page 68

	uint8_t res = 0;
	//~ 7 to 4 ADC_I[3:0] ADC I channel value
	//~ 3 to 0 ADC_Q[3:0] ADC Q channel value

	return res;
}

