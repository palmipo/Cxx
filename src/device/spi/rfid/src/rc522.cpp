#include "rc522.h"
#include "spi.h"

SPI::RC522:RC522(SPI * spi)
_spi(spi)
{
}

SPI::RC522::~RC522()
{
}

u8 SPI::RC522::readAddress(u8 adr)
{
	return (1<<7) | ((addr & 0x3F) << 1);
}

u8 SPI::RC522::writeAddress(u8 adr)
{
	return ((addr & 0x3F) << 1);
}

u8 SPI::RC522::writeRegister(u8 addr, u8* data, u8* rcv, s32 len)
{
	s32 nb = len + 1;
	u8 snd[nb];
	snd[0] = writeAddress(addr);
	for s32 i=0; i<nb; ++i)
	{
		snd[i+1] = data[i];
	}
	_spi->transfer(snd, rcv, len);
	
	return 0;
}

u8 SPI::RC522::readRegister(u8 addr, u8* rcv, s32 len)
{
	s32 nb = len;
	u8 snd[nb];
	for s32 i=0; i<nb; ++i)
	{
		snd[i] = readAddress(addr+i);
	}
	_spi->transfer(snd, rcv, len);
	
	return 0;
}

/*
void MFRC522::PCD_Reset() {
	PCD_WriteRegister(CommandReg, PCD_SoftReset);	// Issue the SoftReset command.
	// The datasheet does not mention how long the SoftRest command takes to complete.
	// But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg) 
	// Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the crystal + 37,74μs. Let us be generous: 50ms.
	uint8_t count = 0;
	do {
		// Wait for the PowerDown bit in CommandReg to be cleared (max 3x50ms)
		delay(50);
	} while ((PCD_ReadRegister(CommandReg) & (1 << 4)) && (++count) < 3);
} // End PCD_Reset()
*/
void SPI::RC522::reset()
{
	writeRegister(1, 0x0F);
	uint8_t count = 0;
	do {
		// Wait for the PowerDown bit in CommandReg to be cleared (max 3x50ms)
		delay(50);
	} while ((readRegister(1) & (1 << 4)) && (++count) < 3);
}

/*
bool MFRC522::PCD_PerformSelfTest() {
	// This follows directly the steps outlined in 16.1.1
	// 1. Perform a soft reset.
	PCD_Reset();
	
	// 2. Clear the internal buffer by writing 25 bytes of 00h
	byte ZEROES[25] = {0x00};
	PCD_WriteRegister(FIFOLevelReg, 0x80);		// flush the FIFO buffer
	PCD_WriteRegister(FIFODataReg, 25, ZEROES);	// write 25 bytes of 00h to FIFO
	PCD_WriteRegister(CommandReg, PCD_Mem);		// transfer to internal buffer
	
	// 3. Enable self-test
	PCD_WriteRegister(AutoTestReg, 0x09);
	
	// 4. Write 00h to FIFO buffer
	PCD_WriteRegister(FIFODataReg, 0x00);
	
	// 5. Start self-test by issuing the CalcCRC command
	PCD_WriteRegister(CommandReg, PCD_CalcCRC);
	
	// 6. Wait for self-test to complete
	byte n;
	for (uint8_t i = 0; i < 0xFF; i++) {
		// The datasheet does not specify exact completion condition except
		// that FIFO buffer should contain 64 bytes.
		// While selftest is initiated by CalcCRC command
		// it behaves differently from normal CRC computation,
		// so one can't reliably use DivIrqReg to check for completion.
		// It is reported that some devices does not trigger CRCIRq flag
		// during selftest.
		n = PCD_ReadRegister(FIFOLevelReg);
		if (n >= 64) {
			break;
		}
	}
	PCD_WriteRegister(CommandReg, PCD_Idle);		// Stop calculating CRC for new content in the FIFO.
	
	// 7. Read out resulting 64 bytes from the FIFO buffer.
	byte result[64];
	PCD_ReadRegister(FIFODataReg, 64, result, 0);
	
	// Auto self-test done
	// Reset AutoTestReg register to be 0 again. Required for normal operation.
	PCD_WriteRegister(AutoTestReg, 0x00);
	
	// Determine firmware version (see section 9.3.4.8 in spec)
	byte version = PCD_ReadRegister(VersionReg);
	
	// Pick the appropriate reference values
	const byte *reference;
	switch (version) {
		case 0x88:	// Fudan Semiconductor FM17522 clone
			reference = FM17522_firmware_reference;
			break;
		case 0x90:	// Version 0.0
			reference = MFRC522_firmware_referenceV0_0;
			break;
		case 0x91:	// Version 1.0
			reference = MFRC522_firmware_referenceV1_0;
			break;
		case 0x92:	// Version 2.0
			reference = MFRC522_firmware_referenceV2_0;
			break;
		default:	// Unknown version
			return false; // abort test
	}
	
	// Verify that the results match up to our expectations
	for (uint8_t i = 0; i < 64; i++) {
		if (result[i] != pgm_read_byte(&(reference[i]))) {
			return false;
		}
	}
	
	// Test passed; all is good.
	return true;
} // End PCD_PerformSelfTest()
*/
