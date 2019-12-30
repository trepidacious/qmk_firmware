#include "gml1.h"

#include "ch.h"
#include "hal.h"

void matrix_init_kb(void) {
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(1000);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(1000);
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(500);
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(250);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(250);
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(100);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(100);
    palSetPad(GPIOD, GPIOD_LED3);       /* Orange.  */
    chThdSleepMilliseconds(50);
    palClearPad(GPIOD, GPIOD_LED3);     /* Orange.  */
    chThdSleepMilliseconds(50);
}
