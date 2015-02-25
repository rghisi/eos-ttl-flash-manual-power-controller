/*
 * main.cpp
 *
 *  Created on: 12/02/2015
 *      Author: ghisi
 */



#include <stdint.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "GUI.h"
#include "TTLFlash.h"

#define F_CPU 1000000UL	/* CPU clock in Hertz */

GUI gui(&DDRC, &PORTC);
TTLFlash ttlFlash(&DDRB, &PORTB);

uint8_t timerZero = 0;

int main() {
	uint8_t coarsePower = gui.getCoarsePower();
	uint8_t totalPower = ((coarsePower + 1) * 2) + coarsePower - gui.getFinePower();
	ttlFlash.setPower(totalPower);

	//	setupINT0()
	DDRD = 0x00;/* use PortD for input (switches) */
	PORTD = 255; //pullup PORTD
	MCUCR = (1<<ISC11)|(1<<ISC01); //falling edge int0 e int1
	GICR = (1<<INT0) | (1<<INT1); //ligando int0 e int1

	//	setupTimer0();
	TCCR0 |= (_BV(CS02));//|(1<<CS00);
	TIMSK |= (_BV(TOIE0));
	TCNT0 = 0;

	TCCR1A = 0;
	TCCR1B = 0;
	TCCR1B &= ~(_BV(CS10));
	TCCR1B |= (_BV(WGM12));
	TIMSK |= (_BV(OCIE1A));

	sei();				//Enable Global Interrupt
	set_sleep_mode(0);
	sleep_enable();
	while (1) {
		//sleep_cpu();
	}
}


ISR(TIMER0_OVF_vect) {
	switch (timerZero) {
		case 0:
			gui.showPower();
			break;
		case 2:
			gui.unshowPower();
			break;
		case 20:
			timerZero = 255;
			break;
		default:
			break;
	}
	timerZero++;
}

ISR(INT0_vect) {
	gui.cycleCoarsePower();
	volatile uint8_t coarsePower = gui.getCoarsePower();
	volatile uint8_t totalPower = coarsePower + 1 + coarsePower + 1 + coarsePower;
	ttlFlash.setPower(totalPower);
	gui.showPower();
	timerZero = 250;
}

ISR(INT1_vect) {
	ttlFlash.startQuench();
}

ISR(TIMER1_COMPA_vect) {
	cli();
	ttlFlash.endQuench();
	sei();
}
