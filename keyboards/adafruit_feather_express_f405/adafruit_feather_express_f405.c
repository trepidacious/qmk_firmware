#include "adafruit_feather_express_f405.h"

#include "ch.h"
#include "hal.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
    // palTogglePad(GPIOD, GPIOD_LED3);       /* Orange.  */

    // Make the scan thread allow context switches (in case it has no sleeps etc.)
    chThdYield();

	matrix_scan_user();
}
