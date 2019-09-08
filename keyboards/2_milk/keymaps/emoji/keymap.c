#include QMK_KEYBOARD_H

#define COUNT 4
const char *strs[COUNT] = {
  "1f601",
  "1f602",
  "1f603",
  "0CA0 005F 0CA0"
//   "00AF 005C 005F 0028 30C4 0029 005F 002F 00AF",
};
int cursor = 0;

enum custom_keycodes {
  UP,
  DOWN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
          UP,
          DOWN
          )
};

void move(bool up, bool delete) {
  int i = 0;

  if (delete) {
    SEND_STRING(SS_TAP(X_BSPACE));

    for (i = 0; i < strlen(strs[cursor]); i++) {
      if (strs[cursor][i] == ' ') {
        SEND_STRING(SS_TAP(X_BSPACE));
      }
    }
  }

  if (up) {
    cursor--;
    if (cursor < 0) cursor = COUNT - 1;
  } else {
    cursor++;
    if (cursor >= COUNT) cursor = 0;
  }

  send_unicode_hex_string(strs[cursor]);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UP:
      if (record->event.pressed) {
        move(true, true);
      } else {
      }
      break;
    case DOWN:
      if (record->event.pressed) {
        move(true, true);
      } else {
      }
      break;
  }
  return true;
};

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    // TODO pick mode based on keys pressed
    set_unicode_input_mode(UC_LNX);
}
