#include "gml1.h"

#include "ch.h"
#include "hal.h"
#include <string.h>

// Each hand (master and slave) has half the rows of the matrix
#define ROWS_PER_HAND (MATRIX_ROWS / 2)
#define SMATRIX_SIZE (ROWS_PER_HAND * sizeof(matrix_row_t))

enum serial_transaction_id {
    GET_SLAVE_MATRIX = 0,
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#    endif
};

// Copy of the matric on the slave, for SlaveThread to send when queried
static matrix_row_t smatrix[ROWS_PER_HAND];
// static mutex_t smatrix_mtx;

/*
 * This thread runs on the slave and responds to transactions initiated
 * by the master
 */
static THD_WORKING_AREA(waSlaveThread, 2048);
static THD_FUNCTION(SlaveThread, arg) {
  (void)arg;
  chRegSetThreadName("slave_transport");
  while (true) {
    enum serial_transaction_id tid = sdGet(&SD3);
    if (tid == GET_SLAVE_MATRIX) {
        // chMtxLock(&smatrix_mtx);
        sdWrite(&SD3, smatrix, SMATRIX_SIZE);
        // chMtxUnlock(&smatrix_mtx);
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

    // Make the scan thread allow context switches (in case it has no sleeps etc.)
    chThdYield();

	matrix_scan_user();
}

bool is_keyboard_master(void) {
    // TODO Can we find out whether we are left or right from qmk?
    setPinInput(SPLIT_HAND_PIN);
    bool master = readPin(SPLIT_HAND_PIN);

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

    // Slave has LED off initially
    setPinOutput(LINE_D13);
    writePin(LINE_D13, 0);

    // Start transport thread
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO - 10, SlaveThread, NULL);
}

bool transport_master(matrix_row_t matrix[]) {
    // Read data from slave and set matrix
    sdPut(&SD3, GET_SLAVE_MATRIX);
    msg_t read_result = sdReadTimeout(&SD3, smatrix, SMATRIX_SIZE, MS2ST(5));
    if (read_result < 0) {
        // Error, e.g. timeout
        return false;
    } else {
        memcpy(matrix, smatrix, SMATRIX_SIZE);
        return true;
    }
}

void transport_slave(matrix_row_t matrix[]) {
    // chMtxLock(&smatrix_mtx);
    memcpy(smatrix, matrix, SMATRIX_SIZE);
    // chMtxUnlock(&smatrix_mtx);
}
