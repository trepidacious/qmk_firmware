/* Copyright 2019 Sebastian Williams
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0xB195
#define DEVICE_VER      0x0001
#define MANUFACTURER    trepidacious
#define PRODUCT         Mountain Lizard 5
#define DESCRIPTION     A Mighty 5 Key Keyboard

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 1

/* Mountain Lizard 5 default pinout, see https://i.imgur.com/wMNx2u6.png */
#define DIRECT_PINS { \
    {D4}, \
    {C6}, \
    {D7}, \
    {B4}, \
    {E6} \
}
#define UNUSED_PINS

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B6
#define RGBLED_NUM 2
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#endif
