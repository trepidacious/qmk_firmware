#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          KC_UP,
          KC_DOWN
          )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    // TODO pick mode based on keys pressed

    matrix_scan();
    wait_ms(10);
    matrix_scan();

    if (matrix_get_row(0) && matrix_get_row(1)) {
      // // Jump to bootloader.
      bootloader_jump();
    } else if (matrix_get_row(0)) {
      set_unicode_input_mode(UC_OSX);
    } else if (matrix_get_row(1)) {
      set_unicode_input_mode(UC_LNX);
    } else {
      set_unicode_input_mode(UC_WINC);
    }

}