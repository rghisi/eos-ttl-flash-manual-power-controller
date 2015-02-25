#include <stdint.h>
#include <avr/interrupt.h>

class GUI {

public:
	GUI(volatile uint8_t *ddr, volatile uint8_t *port);
	void showPower();
	void unshowPower();
	volatile void cycleCoarsePower();
	volatile uint8_t getCoarsePower();
	volatile uint8_t getFinePower();

private:
	volatile uint8_t *port;
	volatile uint8_t coarsePower;
	volatile uint8_t finePower;
	uint8_t portPowerAvailable[18];
	void populatePowerAvaiable();
};

