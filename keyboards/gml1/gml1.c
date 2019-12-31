#include "gml1.h"

#include "ch.h"
#include "hal.h"

void matrix_init_kb(void) {
	// put your keyboard start-up code here
	// runs once when the firmware starts up

    // This delay seems to allow USB to enumerate properly, without this we get read failures
    // and USB device is not identified.
    // This seems to need 380ms to identify properly (to about the nearest 10ms)
    chThdSleepMilliseconds(1500);

	matrix_init_user();
}

void matrix_scan_kb(void) {
	// put your looping keyboard code here
	// runs every cycle (a lot)
    palTogglePad(GPIOD, GPIOD_LED3);       /* Orange.  */

	matrix_scan_user();
}
