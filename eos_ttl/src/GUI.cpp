#include "GUI.h"

GUI::GUI(volatile uint8_t *ddr, volatile uint8_t *port) {
	*ddr = 255;
	this->port = port;
	coarsePower = 0;
	finePower = 0;
	populatePowerAvaiable();
}

volatile uint8_t GUI::getCoarsePower() {
	return coarsePower;
}

volatile uint8_t GUI::getFinePower() {
	return finePower;
}

volatile void GUI::cycleCoarsePower() {
	coarsePower++;
	if (coarsePower > 5) {
		coarsePower = 0;
	}
}

void GUI::showPower() {
	*port = portPowerAvailable[coarsePower];
}

void GUI::unshowPower() {
	*port = 0;
}

void GUI::populatePowerAvaiable() {
	portPowerAvailable[0] = 0b00000001;
	portPowerAvailable[1] = 0b00000010;
	portPowerAvailable[2] = 0b00000100;
	portPowerAvailable[3] = 0b00001000;
	portPowerAvailable[4] = 0b00010000;
	portPowerAvailable[5] = 0b00100000;
}
