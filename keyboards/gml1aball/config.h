/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6464
#define DEVICE_VER      0x0001
/* in python2: list(u"whatever".encode('utf-16-le')) */
/*   at most 32 characters or the ugly hack in usb_main.c borks */
#define MANUFACTURER QMK
#define PRODUCT GML1
#define DESCRIPTION Great Mountain Lizard 1

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { LINE_D10, LINE_D11, LINE_D12, LINE_D13, LINE_D9, LINE_D6, LINE_D5, LINE_RX_D0 }
#define MATRIX_COL_PINS { LINE_A0, LINE_A1, LINE_A2, LINE_A3, LINE_A4, LINE_A5 }

#define DIODE_DIRECTION COL2ROW

// /* key matrix size */
// #define MATRIX_ROWS 2
// #define MATRIX_COLS 1

// /* Direct connections on PC6 and PC7, which are D6 and D5 */
// #define DIRECT_PINS { {PAL_LINE(GPIOC, 6)}, {PAL_LINE(GPIOC, 7)} }

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
// #define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN LINE_D8_NEOPIX
#define RGBLED_NUM 1
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif

// #define SPLIT_HAND_PIN LINE_D12

#define DEBUG_MATRIX_SCAN_RATE

// The bank of pins (GPIOA, GPIOB, GPIOC) to use for SCL
#define I2C1_SCL_BANK GPIOB

// The bank of pins (GPIOA, GPIOB, GPIOC) to use for SDA
#define I2C1_SDA_BANK GPIOB

// The pin number for the SCL pin (0-15)
#define I2C1_SCL 6

// The pin number for the SCL pin (0-15)
#define I2C1_SDA 7

