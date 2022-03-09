#ifndef NFRC522_H
#define NFRC522_H

#include <cstdint>

class PIA;
class CtrlSPI;
class MFRC522
{
public:
	MFRC522(CtrlSPI * ctrl, PIA * irq = 0, PIA * rst = 0);
	virtual ~MFRC522();

void init();
void softReset();

uint8_t readRegister (uint8_t addr);
void writeRegister (uint8_t addr, uint8_t val);

void setCommandReg(uint8_t RcvOff, uint8_t PowerDown, uint8_t Command);
uint8_t commandReg(uint8_t * RcvOff, uint8_t * PowerDown, uint8_t * Command);

uint8_t ComlEnReg(uint8_t IRqInv, uint8_t TxIEn, uint8_t RxIEn, uint8_t IdleIEn, uint8_t HiAlertIEn, uint8_t LoAlertIEn, uint8_t ErrIEn, uint8_t TimerIEn);
uint8_t DivlEnReg(uint8_t IRQPushPull, uint8_t MfinActIEn, uint8_t CRCIEn);
uint8_t ComIrqReg(uint8_t ComIrqReg, uint8_t TxIRq, uint8_t RxIRq, uint8_t IdleIRq, uint8_t HiAlertIRq, uint8_t LoAlertIRq, uint8_t ErrIRq, uint8_t TimerIRq);
uint8_t DivIrqReg(uint8_t Set2, uint8_t MfinActIRq, uint8_t CRCIRq);
uint8_t ErrorReg(uint8_t WrErr, uint8_t TempErr, uint8_t BufferOvfl, uint8_t CollErr, uint8_t CRCErr, uint8_t ParityErr, uint8_t ProtocolErr);
uint8_t Status1Reg(uint8_t CRCOk, uint8_t CRCReady, uint8_t IRq, uint8_t TRunning, uint8_t HiAlert, uint8_t LoAlert);
uint8_t Status2Reg(uint8_t TempSensClear, uint8_t I2CForceHS, uint8_t MFCrypto1On, uint8_t ModemState);
uint8_t FIFODataReg ();
uint8_t FIFOLevelReg ();
uint8_t WaterLevelReg ();
uint8_t ControlReg ();
uint8_t BitFramingReg ();
uint8_t CollReg ();
uint8_t ModeReg ();
uint8_t TxModeReg ();
uint8_t RxModeReg ();
uint8_t TxControlReg ();
uint8_t TxASKReg ();
uint8_t TxSelReg ();
uint8_t RxSelReg ();
uint8_t RxThresholdReg ();
uint8_t DemodReg ();
uint8_t MfTxReg ();
uint8_t MfRxReg ();
uint8_t SerialSpeedReg ();
uint8_t CRCResultReg ();
uint8_t ModWidthReg ();
uint8_t RFCfgReg ();
uint8_t GsNReg ();
uint8_t CWGsPReg ();
uint8_t ModGsPReg ();
uint8_t TModeReg ();
uint8_t TPrescalerReg ();
uint16_t TReloadReg ();
uint16_t TCounterValReg ();
uint8_t TestSel1Reg ();
uint8_t TestSel2Reg ();
uint8_t TestPinEnReg ();
uint8_t TestPinValueReg();
uint8_t TestBusReg();
uint8_t AutoTestReg();
uint8_t VersionReg(uint8_t * chiptype, uint8_t * version);
uint8_t AnalogTestReg();
uint8_t TestDAC1Reg();
uint8_t TestDAC2Reg();
uint8_t TestADCReg();

private:
	CtrlSPI * _spi;
	PIA * _irq_gpio;
	PIA * _rst_gpio;
};

#endif /* NFRC522_H */

