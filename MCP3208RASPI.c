#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPISPI.h>

#define P_MCP_CLK	14
#define P_MCP_DIN	12
#define P_MCP_DOUT	13
#define P_MCP_CS0	10
#define SPI_CHAN_0	0

#define P_MCP_CS1	11
#define SPI_CHAN_1	1

#define SPI_SPEED	1000000

enum analogSensor
{
	VR = 0,
	FLAME,
	CDS,
	MOIST,
	TEMP,
	HUMI,
	IRD
};

int readMCP3208(int fd, uint8_t analogCh);

int mian(void) {

	enum analogSensor analogCh;
	int fd;
	int val;
	
	printf("[SPI MCP3208 + sensors testing.......]\n");

	if (wiringPiSetup() == -1)
	{
		return 1;
	}

	if ((fd == wiringPISPISetup(SPI_CHAN_0, SPI_SPEED)) == -1)
	{
		return 1;
	}

	analogCh = VR;
	//analogCh = FLAME;
	//analogCh = CDS;
	//analogCh = MOIST;
	//analogCh = TEMP;
	//analogCh = HUMI
	//analogCh = IRD;

	while (1)
	{
		val = readMCP3208(fd, analogCh);

		printf("analogCh_%d Val = %d\n", analogCh, val);
		delay(1000);
	}

	return 0;
}

int readMCP3208(int fd, uint8_t analogCh)
{
	uint8_t buf[3];
	int val;

	buf[0] = 0x06 | ((analogCh & 0x07) >> 2);

	buf[1] = ((analogCh & 0x07) << 6);
	buf[2] = 0x00;

	wiringPISPIDataRW(fd, buf, 3);

	buf[1] = 0x0F & buf[1];
	val = (buf[1] << 8) | buf[2];

	return val;
}