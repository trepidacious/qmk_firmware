#include "gml1.h"
#include QMK_KEYBOARD_H
#include "i2c_master.h"

// #include "ch.h"
// #include "hal.h"
// #include <string.h>

#define ALPHANUM_ADDRESS (0x70 << 1)
// TODO assume timeout in ms?
#define ALPHANUM_TIMEOUT 50		
// Maximum is 15
#define ALPHANUM_DEFAULT_BRIGHTNESS 1

#define HT16K33_BLINK_CMD 0x80       ///< I2C register for BLINK setting
#define HT16K33_BLINK_DISPLAYON 0x01 ///< I2C value for steady on
#define HT16K33_BLINK_OFF 0          ///< I2C value for steady off
#define HT16K33_BLINK_2HZ 1          ///< I2C value for 2 Hz blink
#define HT16K33_BLINK_1HZ 2          ///< I2C value for 1 Hz blink
#define HT16K33_BLINK_HALFHZ 3       ///< I2C value for 0.5 Hz blink

#define HT16K33_CMD_BRIGHTNESS 0xE0 ///< I2C register for BRIGHTNESS setting
#define HT16K33_OSC_ON 0x21

static uint8_t alpha_data[20];

static uint16_t displaybuffer[8]; ///< Raw display data

static const uint16_t alphafonttable[] PROGMEM = {

    0b0000000000000001, 0b0000000000000010, 0b0000000000000100,
    0b0000000000001000, 0b0000000000010000, 0b0000000000100000,
    0b0000000001000000, 0b0000000010000000, 0b0000000100000000,
    0b0000001000000000, 0b0000010000000000, 0b0000100000000000,
    0b0001000000000000, 0b0010000000000000, 0b0100000000000000,
    0b1000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0000000000000000, 0b0000000000000000, 0b0000000000000000,
    0b0001001011001001, 0b0001010111000000, 0b0001001011111001,
    0b0000000011100011, 0b0000010100110000, 0b0001001011001000,
    0b0011101000000000, 0b0001011100000000,
    0b0000000000000000, //
    0b0000000000000110, // !
    0b0000001000100000, // "
    0b0001001011001110, // #
    0b0001001011101101, // $
    0b0000110000100100, // %
    0b0010001101011101, // &
    0b0000010000000000, // '
    0b0010010000000000, // (
    0b0000100100000000, // )
    0b0011111111000000, // *
    0b0001001011000000, // +
    0b0000100000000000, // ,
    0b0000000011000000, // -
    0b0000000000000000, // .
    0b0000110000000000, // /
    0b0000110000111111, // 0
    0b0000000000000110, // 1
    0b0000000011011011, // 2
    0b0000000010001111, // 3
    0b0000000011100110, // 4
    0b0010000001101001, // 5
    0b0000000011111101, // 6
    0b0000000000000111, // 7
    0b0000000011111111, // 8
    0b0000000011101111, // 9
    0b0001001000000000, // :
    0b0000101000000000, // ;
    0b0010010000000000, // <
    0b0000000011001000, // =
    0b0000100100000000, // >
    0b0001000010000011, // ?
    0b0000001010111011, // @
    0b0000000011110111, // A
    0b0001001010001111, // B
    0b0000000000111001, // C
    0b0001001000001111, // D
    0b0000000011111001, // E
    0b0000000001110001, // F
    0b0000000010111101, // G
    0b0000000011110110, // H
    0b0001001000000000, // I
    0b0000000000011110, // J
    0b0010010001110000, // K
    0b0000000000111000, // L
    0b0000010100110110, // M
    0b0010000100110110, // N
    0b0000000000111111, // O
    0b0000000011110011, // P
    0b0010000000111111, // Q
    0b0010000011110011, // R
    0b0000000011101101, // S
    0b0001001000000001, // T
    0b0000000000111110, // U
    0b0000110000110000, // V
    0b0010100000110110, // W
    0b0010110100000000, // X
    0b0001010100000000, // Y
    0b0000110000001001, // Z
    0b0000000000111001, // [
    0b0010000100000000, //
    0b0000000000001111, // ]
    0b0000110000000011, // ^
    0b0000000000001000, // _
    0b0000000100000000, // `
    0b0001000001011000, // a
    0b0010000001111000, // b
    0b0000000011011000, // c
    0b0000100010001110, // d
    0b0000100001011000, // e
    0b0000000001110001, // f
    0b0000010010001110, // g
    0b0001000001110000, // h
    0b0001000000000000, // i
    0b0000000000001110, // j
    0b0011011000000000, // k
    0b0000000000110000, // l
    0b0001000011010100, // m
    0b0001000001010000, // n
    0b0000000011011100, // o
    0b0000000101110000, // p
    0b0000010010000110, // q
    0b0000000001010000, // r
    0b0010000010001000, // s
    0b0000000001111000, // t
    0b0000000000011100, // u
    0b0010000000000100, // v
    0b0010100000010100, // w
    0b0010100011000000, // x
    0b0010000000001100, // y
    0b0000100001001000, // z
    0b0000100101001001, // {
    0b0001001000000000, // |
    0b0010010010001001, // }
    0b0000010100100000, // ~
    0b0011111111111111,
};

static void start(void) {
	i2c_start(ALPHANUM_ADDRESS);
}

static void write(uint8_t a) {
	alpha_data[0] = a;
	i2c_transmit(ALPHANUM_ADDRESS, alpha_data, 1, ALPHANUM_TIMEOUT);
}

static void stop(void) {
	i2c_stop();
}

static void set_brightness(uint8_t b) {
  if (b > 15)
    b = 15;
  start();
  write(HT16K33_CMD_BRIGHTNESS | b);
  stop();
}

static void set_blink_rate(uint8_t b) {
	start();
	if (b > 3) b = 0; // turn off if not sure

	write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1));
	stop();
}

void write_display(void) {

  
	// TODO Use one transfer?
	alpha_data[0] = 0x00; // start at address $00

	for (uint8_t i = 0; i < 8; i++) {
		alpha_data[1 + i * 2] = displaybuffer[i] & 0xFF;
		alpha_data[1 + i * 2 + 1] = displaybuffer[i] >> 8;
	}

    start();
	i2c_transmit(ALPHANUM_ADDRESS, alpha_data, 1 + 8 * 2, ALPHANUM_TIMEOUT);
  	stop();
}

void write_digit_raw(uint8_t n, uint16_t bitmask) {
  displaybuffer[n] = bitmask;
}

void write_digit_ascii(uint8_t n, uint8_t a, bool d) {
  uint16_t font = pgm_read_word(alphafonttable + a);

  displaybuffer[n] = font;

  /*
  Serial.print(a, DEC);
  Serial.print(" / '"); Serial.write(a);
  Serial.print("' = 0x"); Serial.println(font, HEX);
  */

  if (d)
    displaybuffer[n] |= (1 << 14);
}

void clear(void) {
  for (uint8_t i = 0; i < 8; i++) {
    displaybuffer[i] = 0;
  }
}

static void init(void) {
	start();
	write(HT16K33_OSC_ON);
	stop();
}

void matrix_init_kb(void) {
	matrix_init_user();

	i2c_init();
	init();

	// Clear memory, may not be empty
	clear();
	write_digit_ascii(0, 'G', false);
	write_digit_ascii(1, 'M', false);
	write_digit_ascii(2, 'L', false);
	write_digit_ascii(3, '1', false);
	write_display();

	set_blink_rate(HT16K33_BLINK_OFF);
	set_brightness(ALPHANUM_DEFAULT_BRIGHTNESS);
}

void matrix_scan_kb(void) {
	matrix_scan_user();
}

// bool is_keyboard_master(void) {
//     // TODO Can we find out whether we are left or right from qmk?
//     setPinInput(SPLIT_HAND_PIN);
//     bool master = readPin(SPLIT_HAND_PIN);

//     return master;
// }


// // Each hand (master and slave) has half the rows of the matrix
// #define ROWS_PER_HAND (MATRIX_ROWS / 2)
// #define SMATRIX_SIZE (ROWS_PER_HAND * sizeof(matrix_row_t))

// enum serial_transaction_id {
//     GET_SLAVE_MATRIX = 0,
// #    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
//     PUT_RGBLIGHT,
// #    endif
// };

// // Copy of the matric on the slave, for SlaveThread to send when queried
// static matrix_row_t smatrix[ROWS_PER_HAND];
// // static mutex_t smatrix_mtx;

// static SerialConfig serial_cfg = {
//     1000000,
//     0,
//     0,
//     USART_CR3_HDSEL
// };

// /*
//  * This thread runs on the slave and responds to transactions initiated
//  * by the master
//  */
// static THD_WORKING_AREA(waSlaveThread, 2048);
// static THD_FUNCTION(SlaveThread, arg) {
//   (void)arg;
//   chRegSetThreadName("slave_transport");
//   while (true) {
//     enum serial_transaction_id tid = sdGet(&SD3);
//     if (tid == GET_SLAVE_MATRIX) {
//         // chMtxLock(&smatrix_mtx);
//         sdWrite(&SD3, smatrix, SMATRIX_SIZE);
//         // chMtxUnlock(&smatrix_mtx);

//         // TODO can we avoid the need to read back our own data?
//         // Read back what we wrote...
//         sdRead(&SD3, smatrix, SMATRIX_SIZE);
//     }
//   }
// }

// bool transport_master(matrix_row_t matrix[]) {

//     // Clear the buffer
//     while(sdGetTimeout(&SD3, TIME_IMMEDIATE) != MSG_TIMEOUT);

//     // Read data from slave and set matrix
//     sdPut(&SD3, GET_SLAVE_MATRIX);
//     // Read back and discard what we just wrote
//     sdGet(&SD3);
//     msg_t read_result = sdReadTimeout(&SD3, smatrix, SMATRIX_SIZE, MS2ST(5));
//     if (read_result < 0) {
//         // Error, e.g. timeout
//         return false;

//     } else {
//         memcpy(matrix, smatrix, SMATRIX_SIZE);
//         palToggleLine(LINE_D13);
//         return true;
//     }
// }

// void transport_slave(matrix_row_t matrix[]) {
//     // chMtxLock(&smatrix_mtx);
//     memcpy(smatrix, matrix, SMATRIX_SIZE);
//     // chMtxUnlock(&smatrix_mtx);
// }


// /**
//  * Configure uart for split-keyboard comms
//  */
// void gml1_init_uart(void) {
//     // // Default settings are fine - set speed in halconf.h
//     // sdStart(&SD3, NULL);
//     // // USART3 is AF7 on these pins
//     // palSetPadMode(GPIOB, GPIOB_TX_D1, PAL_MODE_ALTERNATE(7));
//     // palSetPadMode(GPIOB, GPIOB_RX_D0, PAL_MODE_ALTERNATE(7));

//     // Configure in half-duplex - note this needs a strong pull-up on
//     // TX pin to work at higher speeds.
//     sdStart(&SD3, &serial_cfg);

//     // USART3 is AF7 on TX, which must be a open drain when not controlled
//     // by peripheral
//     const uint32_t modeTx = PAL_MODE_ALTERNATE(7) | PAL_STM32_OTYPE_OPENDRAIN
//       | PAL_MODE_INPUT_PULLUP | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_MODE_ALTERNATE;

//     palSetPadMode(GPIOB, GPIOB_TX_D1, modeTx);
// }

// void transport_master_init(void) {

//     gml1_init_uart();

//     // Master has LED on
//     setPinOutput(LINE_D13);
//     writePin(LINE_D13, 1);

// }

// void transport_slave_init(void){

//     gml1_init_uart();

//     // Slave has LED off initially
//     setPinOutput(LINE_D13);
//     writePin(LINE_D13, 0);

//     // Start transport thread
//     chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO - 10, SlaveThread, NULL);
// }
