/*
 * TTLFlash.cpp
 *
 *  Created on: 12/02/2015
 *      Author: ghisi
 */

#include "TTLFlash.h"


TTLFlash::TTLFlash(volatile uint8_t *ddr, volatile uint8_t *port) {
	*ddr = 255;
	*port = 255; //pullup PORTD
	this->port = port;
	power = P1_8;
	powerTiming[17] = 4000;
	powerTiming[16] = 4000;
	powerTiming[15] = 4000;
	powerTiming[14] = 2000;
	powerTiming[13] = 2000;
	powerTiming[12] = 2000;
	powerTiming[11] = 1000;
	powerTiming[10] = 1000;
	powerTiming[9] = 1000;
	powerTiming[8] = 500;
	powerTiming[7] = 500;
	powerTiming[6] = 500;
	powerTiming[5] = 250;
	powerTiming[4] = 250;
	powerTiming[3] = 250;
	powerTiming[2] = 125;
	powerTiming[1] = 125;
	powerTiming[0] = 125;
	setup();
}

void TTLFlash::setup() {
	endQuench();
}

void volatile TTLFlash::setPower(uint8_t power) {
	OCR1A = powerTiming[power];
	this->power = power;
}

void volatile TTLFlash::setupQuenchTime() {
	OCR1A = powerTiming[power];
}

void TTLFlash::startQuench() {
	*port = 0;
	TCCR1B |= (_BV(CS10)); //start timer1
}

void TTLFlash::endQuench() {
	*port = 255;
	TCCR1B &= ~(_BV(CS10)); //stop timer1
}

