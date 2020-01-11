#include "gml1.h"

// #include "split_common/split_util.h"
// #include "matrix.h"
// #include "keyboard.h"
// #include "config.h"
// #include "timer.h"
// #include "quantum.h"

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

bool is_keyboard_master(void) {
    // TODO call this instead
    // return is_keyboard_left();

    setPinInput(SPLIT_HAND_PIN);
    bool master = readPin(SPLIT_HAND_PIN);

    // setPinOutput(LINE_D13);
    // writePin(LINE_D13, master);

    return master;
}

/**
 * Configure uart for split-keyboard comms
 */
void gml1_init_uart(void) {
    // Default settings are fine - set speed in halconf.h
    sdStart(&SD3, NULL);
    // USART3 is AF7 on these pins
    palSetPadMode(GPIOB, GPIOB_TX_D1, PAL_MODE_ALTERNATE(7));
    palSetPadMode(GPIOB, GPIOB_RX_D0, PAL_MODE_ALTERNATE(7));
}

void transport_master_init(void) {

    gml1_init_uart();

    // Master has LED on
    setPinOutput(LINE_D13);
    writePin(LINE_D13, 1);
}

void transport_slave_init(void){

    gml1_init_uart();

    // Slave has LED off
    setPinOutput(LINE_D13);
    writePin(LINE_D13, 0);
}

// returns false if valid data not received from slave
bool transport_master(matrix_row_t matrix[]) {
    return true;
}

void transport_slave(matrix_row_t matrix[]) {
}
