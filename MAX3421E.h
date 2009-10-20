/*
 * MAX3421E.h
 *
 *  Created on: Oct 13, 2009
 *      Author: fgervais
 */

#ifndef MAX3421E_H_
#define MAX3421E_H_

#include <stdint.h>

class Spi;

class MAX3421E {
public:
	// MAX3421E Registers
	static const uint8_t RCVFIFO	= 1;
	static const uint8_t SNDFIFO	= 2;
	static const uint8_t SUDFIFO	= 3;
	static const uint8_t RCVBC		= 6;
	static const uint8_t SNDBC		= 7;
	static const uint8_t USBIRQ		= 13;
	static const uint8_t USBIEN		= 14;
	static const uint8_t USBCTL		= 15;
	static const uint8_t CPUCTL		= 16;
	static const uint8_t PINCTL		= 17;
	static const uint8_t REVISION	= 18;
	static const uint8_t IOPINS1	= 20;
	static const uint8_t IOPINS2	= 21;
	static const uint8_t GPINJIRQ	= 22;
	static const uint8_t GPINIEN	= 23;
	static const uint8_t GPINPOL	= 24;
	static const uint8_t HIRQ		= 25;
	static const uint8_t HIEN		= 26;
	static const uint8_t MODE		= 27;
	static const uint8_t PERADDR	= 28;
	static const uint8_t HCTL		= 29;
	static const uint8_t HXFR		= 30;
	static const uint8_t HRSL		= 31;

	// Bit definition for RCVBC register
	static const uint8_t RCVBC_BC0			= 0x01;
	static const uint8_t RCVBC_BC1			= 0x02;
	static const uint8_t RCVBC_BC2			= 0x04;
	static const uint8_t RCVBC_BC3			= 0x08;
	static const uint8_t RCVBC_BC4			= 0x10;
	static const uint8_t RCVBC_BC5			= 0x20;
	static const uint8_t RCVBC_BC6			= 0x40;

	// Bit definition for SNDBC register
	static const uint8_t SNDBC_BC0			= 0x01;
	static const uint8_t SNDBC_BC1			= 0x02;
	static const uint8_t SNDBC_BC2			= 0x04;
	static const uint8_t SNDBC_BC3			= 0x08;
	static const uint8_t SNDBC_BC4			= 0x10;
	static const uint8_t SNDBC_BC5			= 0x20;
	static const uint8_t SNDBC_BC6			= 0x40;

	// Bit definition for USBIRQ register
	static const uint8_t USBIRQ_OSCOKIRQ	= 0x01;
	static const uint8_t USBIRQ_NOVBUSIRQ	= 0x02;
	static const uint8_t USBIRQ_VBUSIRQ		= 0x04;

	// Bit definition for USBIEN register
	static const uint8_t USBIEN_OSCOKIE		= 0x01;
	static const uint8_t USBIEN_NOVBUSIE	= 0x02;
	static const uint8_t USBIEN_VBUSIE		= 0x04;

	// Bit definition for USBCTL register
	static const uint8_t USBCTL_PWRDOWN		= 0x01;
	static const uint8_t USBCTL_CHIPRES		= 0x02;

	// Bit definition for CPUCTL register
	static const uint8_t CPUCTL_IE	= 0x01;
	static const uint8_t CPUCTL_PULSEWID0	= 0x04;
	static const uint8_t CPUCTL_PULSEWID1	= 0x08;

	// Bit definition for PINCTL register
	static const uint8_t PINCTL_GPXA		= 0x01;
	static const uint8_t PINCTL_GPXB		= 0x02;
	static const uint8_t PINCTL_POSINT		= 0x04;
	static const uint8_t PINCTL_INTLEVEL	= 0x08;
	static const uint8_t PINCTL_FDUPSPI		= 0x10;
	static const uint8_t PINCTL_EP0INAK		= 0x20;
	static const uint8_t PINCTL_EP2INAK		= 0x40;
	static const uint8_t PINCTL_EP3INAK		= 0x80;

	// Bit definition for IOPINS1 register
	static const uint8_t IOPINS1_GPOUT0		= 0x01;
	static const uint8_t IOPINS1_GPOUT1		= 0x02;
	static const uint8_t IOPINS1_GPOUT2		= 0x04;
	static const uint8_t IOPINS1_GPOUT3		= 0x08;
	static const uint8_t IOPINS1_GPIN0		= 0x10;
	static const uint8_t IOPINS1_GPIN1		= 0x20;
	static const uint8_t IOPINS1_GPIN2		= 0x40;
	static const uint8_t IOPINS1_GPIN3		= 0x80;

	// Bit definition for IOPINS2 register
	static const uint8_t IOPINS2_GPOUT4		= 0x01;
	static const uint8_t IOPINS2_GPOUT5		= 0x02;
	static const uint8_t IOPINS2_GPOUT6		= 0x04;
	static const uint8_t IOPINS2_GPOUT7		= 0x08;
	static const uint8_t IOPINS2_GPIN4		= 0x10;
	static const uint8_t IOPINS2_GPIN5		= 0x20;
	static const uint8_t IOPINS2_GPIN6		= 0x40;
	static const uint8_t IOPINS2_GPIN7		= 0x80;

	// Bit definition for GPINIRQ register
	static const uint8_t GPINIRQ_GPINIRQ0	= 0x01;
	static const uint8_t GPINIRQ_GPINIRQ1	= 0x02;
	static const uint8_t GPINIRQ_GPINIRQ2	= 0x04;
	static const uint8_t GPINIRQ_GPINIRQ3	= 0x08;
	static const uint8_t GPINIRQ_GPINIRQ4	= 0x10;
	static const uint8_t GPINIRQ_GPINIRQ5	= 0x20;
	static const uint8_t GPINIRQ_GPINIRQ6	= 0x40;
	static const uint8_t GPINIRQ_GPINIRQ7	= 0x80;

	// Bit definition for GPINIEN register
	static const uint8_t GPINIEN_GPINIEN0	= 0x01;
	static const uint8_t GPINIEN_GPINIEN1	= 0x02;
	static const uint8_t GPINIEN_GPINIEN2	= 0x04;
	static const uint8_t GPINIEN_GPINIEN3	= 0x08;
	static const uint8_t GPINIEN_GPINIEN4	= 0x10;
	static const uint8_t GPINIEN_GPINIEN5	= 0x20;
	static const uint8_t GPINIEN_GPINIEN6	= 0x40;
	static const uint8_t GPINIEN_GPINIEN7	= 0x80;

	// Bit definition for GPINPOL register
	static const uint8_t GPINPOL_GPINPOL0	= 0x01;
	static const uint8_t GPINPOL_GPINPOL1	= 0x02;
	static const uint8_t GPINPOL_GPINPOL2	= 0x04;
	static const uint8_t GPINPOL_GPINPOL3	= 0x08;
	static const uint8_t GPINPOL_GPINPOL4	= 0x10;
	static const uint8_t GPINPOL_GPINPOL5	= 0x20;
	static const uint8_t GPINPOL_GPINPOL6	= 0x40;
	static const uint8_t GPINPOL_GPINPOL7	= 0x80;

	// Bit definition for HIRQ register
	static const uint8_t HIRQ_BUSEVENTIRQ	= 0x01;
	static const uint8_t HIRQ_RSMREQIRQ		= 0x02;
	static const uint8_t HIRQ_RCVDAVIRQ		= 0x04;
	static const uint8_t HIRQ_SNDBAVIRQ		= 0x08;
	static const uint8_t HIRQ_SUSDNIRQ		= 0x10;
	static const uint8_t HIRQ_CONNIRQ		= 0x20;
	static const uint8_t HIRQ_FRAMEIRQ		= 0x40;
	static const uint8_t HIRQ_HXFRDNIRQ		= 0x80;

	// Bit definition for HIEN register
	static const uint8_t HIEN_BUSEVENTIE	= 0x01;
	static const uint8_t HIEN_RSMREQIE		= 0x02;
	static const uint8_t HIEN_RCVDAVIE		= 0x04;
	static const uint8_t HIEN_SNDBAVIE		= 0x08;
	static const uint8_t HIEN_SUSDNIE		= 0x10;
	static const uint8_t HIEN_CONNIE		= 0x20;
	static const uint8_t HIEN_FRAMEIE		= 0x40;
	static const uint8_t HIEN_HXFRDNIE		= 0x80;

	// Bit definition for MODE register
	static const uint8_t MODE_HOST			= 0x01;
	static const uint8_t MODE_SPEED			= 0x02;
	static const uint8_t MODE_HUBPRE		= 0x04;
	static const uint8_t MODE_SOFKAENAB		= 0x08;
	static const uint8_t MODE_SEPIRQ		= 0x10;
	static const uint8_t MODE_DELAYISO		= 0x20;
	static const uint8_t MODE_DMPULLDN		= 0x40;
	static const uint8_t MODE_DPPULLDN		= 0x80;

	// Bit definition for PERADDR register

	// Bit definition for HCTL register
	static const uint8_t HCTL_BUSRST		= 0x01;
	static const uint8_t HCTL_FRMRST		= 0x02;
	static const uint8_t HCTL_BUSSAMPLE		= 0x04;
	static const uint8_t HCTL_SIGRSM		= 0x08;
	static const uint8_t HCTL_RCVTOG0		= 0x10;
	static const uint8_t HCTL_RCVTOG1		= 0x20;
	static const uint8_t HCTL_SNDTOG0		= 0x40;
	static const uint8_t HCTL_SNDTOG1		= 0x80;

	// Bit definition for HXFR register
	static const uint8_t HXFR_EP0			= 0x01;
	static const uint8_t HXFR_EP1			= 0x02;
	static const uint8_t HXFR_EP2			= 0x04;
	static const uint8_t HXFR_EP3			= 0x08;
	static const uint8_t HXFR_SETUP			= 0x10;
	static const uint8_t HXFR_OUTNIN		= 0x20;
	static const uint8_t HXFR_ISO			= 0x40;
	static const uint8_t HXFR_HS			= 0x80;

	// Bit definition for HRSL register
	static const uint8_t HRSL_HRSLT0		= 0x01;
	static const uint8_t HRSL_HRSLT1		= 0x02;
	static const uint8_t HRSL_HRSLT2		= 0x04;
	static const uint8_t HRSL_HRSLT3		= 0x08;
	static const uint8_t HRSL_RCVTOGRD		= 0x10;
	static const uint8_t HRSL_SNDTOGRD		= 0x20;
	static const uint8_t HRSL_KSTATUS		= 0x40;
	static const uint8_t HRSL_JSTATUS		= 0x80;


	MAX3421E(Spi *spi);
	virtual ~MAX3421E();

	uint8_t writeRegister(uint8_t address, uint8_t data);
	uint8_t writeBytes(uint8_t address, uint8_t *data, uint8_t length);
	uint8_t readRegister(uint8_t address, uint8_t *data);
	uint8_t readBytes(uint8_t address, uint8_t *data, uint8_t length);

private:
	Spi *spi;
};

#endif /* MAX3421E_H_ */
