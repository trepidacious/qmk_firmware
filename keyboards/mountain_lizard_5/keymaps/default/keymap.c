#include QMK_KEYBOARD_H

// enum custom_keycodes {
//   COMMAND = SAFE_RANGE,
// };

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case COMMAND:
//       if (record->event.pressed) {
//         // when keycode QMKBEST is pressed
//         SEND_STRING(SS_DOWN(KC_LCTRL)SS_DOWN(KC_LSHIFT)"P"SS_UP(KC_LSHIFT)SS_UP(KC_LCTRL));
//       } else {
//         // when keycode QMKBEST is released
//       }
//       break;

//   }
//   return true;
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          KC_MEDIA_PLAY_PAUSE,
          KC_MEDIA_NEXT_TRACK,
          KC_AUDIO_VOL_UP,
          KC_AUDIO_VOL_DOWN,
          // LCTL(LSFT(KC_P))
          LGUI(LSFT(KC_P))

          )
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    // TODO pick mode based on keys pressed

    matrix_scan();
    wait_ms(10);
    matrix_scan();

    if (matrix_get_row(0) && matrix_get_row(1) && matrix_get_row(2)) {
      // // Jump to bootloader.
      bootloader_jump();
    } else if (matrix_get_row(0)) {
      set_unicode_input_mode(UC_WINC);
    } else if (matrix_get_row(1)) {
      set_unicode_input_mode(UC_LNX);
    } else {
      set_unicode_input_mode(UC_OSX);
    }

}