#include "gml1.h"

// #include "split_common/split_util.h"
// #include "matrix.h"
// #include "keyboard.h"
// #include "config.h"
// #include "timer.h"
// #include "quantum.h"

#include "ch.h"
#include "hal.h"

volatile uint8_t button = 0;

/*
 * This thread runs on the slave and responds to transactions initiated
 * by the master
 */
static THD_WORKING_AREA(waSlaveThread, 2048);
static THD_FUNCTION(SlaveThread, arg) {
  (void)arg;
  chRegSetThreadName("slave_transport");
  while (true) {
    // writePin(LINE_D13, 0);
    // chThdSleepMilliseconds(500);
    // writePin(LINE_D13, 1);
    // chThdSleepMilliseconds(500);
    uint8_t command = sdGet(&SD3);
    if (command == 1) {
        sdPut(&SD3, button);
    }
  }
}

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

    // palSetPadMode(GPIOB, GPIOB_D10, PAL_MODE_INPUT_PULLUP);

}

void transport_slave_init(void){

    gml1_init_uart();

    // Slave has LED off initially
    setPinOutput(LINE_D13);
    writePin(LINE_D13, 0);

    // Start transport thread
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), NORMALPRIO, SlaveThread, NULL);
}

// returns false if valid data not received from slave
bool transport_master(matrix_row_t matrix[]) {
    // matrix[0] = !readPin(LINE_D10);

    // Read data from slave and set matrix
    sdPut(&SD3, 1);
    // TODO respond to timeout
    uint8_t slave_button = sdGetTimeout(&SD3, MS2ST(5));
    matrix[0] = slave_button;

    return true;
}

void transport_slave(matrix_row_t matrix[]) {
    writePin(LINE_D13, matrix[0]);
    button = matrix[0];
}
