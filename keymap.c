#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "keymap_uk.h"

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
  QUOTES
};

enum planck_layers {
  _BASE,
  _NUMBERS,
  _SYMBOLS_AND_NAV,
  _ADJUST,
  _NAV,
};

#define UNSHIFTED_UK_DQUO KC_2

#define ESCAPE_OR_NUMBERS LT(_NUMBERS, KC_ESCAPE)
#define TAB_OR_SYMBOLS    LT(_SYMBOLS_AND_NAV, KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    ESCAPE_OR_NUMBERS,  KC_Q,     KC_W,     KC_E,      KC_R,      KC_T,        KC_Y,     KC_U,         KC_I,         KC_O,     KC_P,       KC_BSPACE,
    TAB_OR_SYMBOLS,     KC_A,     KC_S,     KC_D,      KC_F,      KC_G,        KC_H,     KC_J,         KC_K,         KC_L,     KC_SCOLON,  QUOTES,
    KC_LSHIFT,          KC_Z,     KC_X,     KC_C,      KC_V,      KC_B,        KC_N,     KC_M,         KC_COMMA,     KC_DOT,   KC_UP,      KC_ENTER,
    KC_LCTRL,           KC_LGUI,  KC_LALT,  KC_MINUS,  KC_EQUAL,  KC_SPACE,/**/XXXXXXX,  KC_LBRACKET,  KC_RBRACKET,  KC_LEFT,  KC_DOWN,    KC_RIGHT
  ),

  [_NUMBERS] = LAYOUT_planck_grid(
    _______,     KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       KC_F6,       KC_F7,       KC_F8,       KC_F9,       KC_F10,      KC_F11,
    KC_0,        KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_F12,
    LGUI(KC_0),  LGUI(KC_1),  LGUI(KC_2),  LGUI(KC_3),  LGUI(KC_4),  LGUI(KC_5),  LGUI(KC_6),  LGUI(KC_7),  LGUI(KC_8),  LGUI(KC_9),  LGUI(KC_0),  XXXXXXX,
    XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,/***/XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX
  ),

  [_SYMBOLS_AND_NAV] = LAYOUT_planck_grid(
    XXXXXXX,  KC_QUESTION,  XXXXXXX,  KC_EXLM,  XXXXXXX,  UK_TILD,    XXXXXXX,        XXXXXXX,  UK_PIPE,   XXXXXXX,          KC_PERC,    KC_DELETE,
    _______,  KC_AMPR,      KC_ASTR,  KC_DLR,   XXXXXXX,  UK_AT,      KC_NONUS_HASH,  XXXXXXX,  XXXXXXX,   UK_PND,           XXXXXXX,    KC_GRAVE,
    XXXXXXX,  XXXXXXX,      XXXXXXX,  KC_CIRC,  XXXXXXX,  XXXXXXX,    XXXXXXX,        XXXXXXX,  KC_SLASH,  KC_NONUS_BSLASH,  KC_PGUP,    XXXXXXX,
    XXXXXXX,  XXXXXXX,      XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,/**/XXXXXXX,        KC_LPRN,  KC_RPRN,   KC_HOME,          KC_PGDOWN,  KC_END
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  AU_ON,    AU_OFF,   AU_TOG,   _______,    _______,  _______,  _______,  _______,  _______,  RESET,
    _______,  _______,  MU_ON,    MU_OFF,   MU_TOG,   _______,    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,/**/XXXXXXX,  _______,  _______,  _______,  _______,  _______
  ),

};

//bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//  switch (keycode) {
//  }
//  return true;
//}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QUOTES: {
      static uint16_t kc;
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          kc = UNSHIFTED_UK_DQUO;
        } else {
          kc = UK_QUOT;
        }
        register_code(kc);
      } else {
        unregister_code(kc);
      }
    }
  }
  return true;
}

// define raise/lower layers so template code below works unchanged
#define _LOWER _NUMBERS
#define _RAISE _SYMBOLS_AND_NAV
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update(bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
    #ifdef MOUSEKEY_ENABLE
      register_code(KC_MS_WH_DOWN);
      unregister_code(KC_MS_WH_DOWN);
    #else
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    #endif
    } else {
    #ifdef MOUSEKEY_ENABLE
      register_code(KC_MS_WH_UP);
      unregister_code(KC_MS_WH_UP);
    #else
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    #endif
    }
  }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
        stop_note(compute_freq_for_midi_note(last_muse_note));
        play_note(compute_freq_for_midi_note(muse_note), 0xF);
        last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
  case RAISE:
  case LOWER:
    return false;
  default:
    return true;
  }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
