/*
 * TTLFlash.h
 *
 *  Created on: 12/02/2015
 *      Author: ghisi
 */

#include <stdint.h>
#include <avr/interrupt.h>

#define P1_1		17	//5
#define P1_1_1_3	16
#define P1_1_2_3	15
#define P1_2		14	//4
#define P1_2_1_3	13
#define P1_2_2_3	12
#define P1_4		11	//3
#define P1_4_1_3	10
#define P1_4_2_3	9
#define P1_8		8	//2
#define P1_8_1_3	7
#define P1_8_2_3	6
#define P1_16		5	//1
#define P1_16_1_3	4
#define P1_16_2_3	3
#define P1_32		2	//0
#define P1_32_1_3	1
#define P1_32_2_3	0


class TTLFlash {

public:
	TTLFlash(volatile uint8_t *ddr, volatile uint8_t *port);
	void volatile setPower(uint8_t power);
	void startQuench();
	void endQuench();

private:
	volatile uint8_t *ddr;
	volatile uint8_t *port;
	uint8_t quenchMask;
	volatile uint8_t power;
	uint16_t powerTiming[18];
	void setup();
	void volatile setupQuenchTime();
};
