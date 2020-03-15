#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "keymap_uk.h"

enum planck_keycodes {
  RGB_SLD = EZ_SAFE_RANGE,
};

enum planck_layers {
  _BASE,
  _SHIFT,
  _DELETE,
  _NAV,
  _SYMBOLS,
  _NUMBERS,
  _JUMP,
  _FUNCTION,
  _ADJUST,
};

//Tap Dance Declarations
enum {
  TD_ESCAPE_OR_NAV = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESCAPE_OR_NAV] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESCAPE, _NAV)
};

#define ESCAPE_OR_NAV   TD(TD_ESCAPE_OR_NAV)
#define SPACE_OR_NAV    LT(_NAV, KC_SPACE)
#define TAB_OR_SYMBOLS  LT(_SYMBOLS, KC_TAB)
#define F_OR_FUNCTION   LT(_FUNCTION, KC_F)
#define J_OR_JUMP       LT(_JUMP, KC_J)
#define N_OR_NUMBERS    LT(_NUMBERS, KC_N)
#define P_OR_DEL        LT(_DELETE, KC_P)
#define SHIFT_LAYER     LM(_SHIFT, MOD_LSFT)
#define TO_BASE         TO(_BASE)

#define L_ROUND_BRACKET     KC_LEFT_PAREN
#define R_ROUND_BRACKET     KC_RIGHT_PAREN
#define L_SQUARE_BRACKET    KC_LBRACKET
#define R_SQUARE_BRACKET    KC_RBRACKET
#define L_SQUIGGLY_BRACKET  KC_LEFT_CURLY_BRACE
#define R_SQUIGGLY_BRACKET  KC_RIGHT_CURLY_BRACE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    ESCAPE_OR_NAV,   KC_Q,     KC_W,     KC_E,      KC_R,          KC_T,            KC_Y,          KC_U,             KC_I,             KC_O,     P_OR_DEL,   KC_BSPACE,
    TAB_OR_SYMBOLS,  KC_A,     KC_S,     KC_D,      F_OR_FUNCTION, KC_G,            KC_H,          J_OR_JUMP,        KC_K,             KC_L,     KC_SCOLON,  UK_QUOT,
    SHIFT_LAYER,     KC_Z,     KC_X,     KC_C,      KC_V,          KC_B,            N_OR_NUMBERS,  KC_M,             KC_COMMA,         KC_DOT,   KC_UP,      KC_ENTER,
    KC_LCTRL,        KC_LGUI,  KC_LALT,  KC_MINUS,  KC_EQUAL,      SPACE_OR_NAV,/**/XXXXXXX,       L_ROUND_BRACKET,  R_ROUND_BRACKET,  KC_LEFT,  KC_DOWN,    KC_RIGHT
  ),

  [_SHIFT] = LAYOUT_planck_grid(
    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,             _______,             _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,             _______,             _______,  _______,  UK_DQUO,
    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,             _______,             _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,/**/XXXXXXX,  L_SQUIGGLY_BRACKET,  R_SQUIGGLY_BRACKET,  _______,  _______,  _______
  ),

  [_DELETE] = LAYOUT_planck_grid(
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  KC_DELETE,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [_NAV] = LAYOUT_planck_grid(
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_PGUP,    KC_BSPACE,  KC_UP,    KC_DELETE,  XXXXXXX,  XXXXXXX,
    TO_BASE,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_PGDOWN,  KC_LEFT,    KC_DOWN,  KC_RIGHT,   XXXXXXX,  XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,    KC_HOME,    XXXXXXX,  KC_END,     XXXXXXX,  XXXXXXX,
    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,/**/XXXXXXX,    XXXXXXX,    XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX
  ),


  [_SYMBOLS] = LAYOUT_planck_grid(
    _______,  KC_QUESTION,  XXXXXXX,  KC_EXLM,  XXXXXXX,  UK_TILD,    XXXXXXX,        XXXXXXX,           UK_PIPE,           XXXXXXX,          KC_PERC,    XXXXXXX,
    _______,  KC_AMPR,      KC_ASTR,  KC_DLR,   XXXXXXX,  UK_AT,      KC_NONUS_HASH,  XXXXXXX,           XXXXXXX,           UK_PND,           XXXXXXX,    KC_GRAVE,
    _______,  XXXXXXX,      XXXXXXX,  KC_CIRC,  XXXXXXX,  XXXXXXX,    XXXXXXX,        XXXXXXX,           KC_SLASH,          KC_NONUS_BSLASH,  KC_PGUP,    XXXXXXX,
    _______,  _______,      _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,/**/XXXXXXX,        L_SQUARE_BRACKET,  R_SQUARE_BRACKET,  KC_HOME,          KC_PGDOWN,  KC_END
  ),

  [_NUMBERS] = LAYOUT_planck_grid(
    KC_0,     KC_1,     KC_2,     KC_3,     XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  KC_0,     KC_1,     KC_2,     KC_3,
    _______,  KC_4,     KC_5,     KC_6,     XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_4,     KC_5,     KC_6,
    _______,  KC_7,     KC_8,     KC_9,     XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_7,     KC_8,     KC_9,
    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [_JUMP] = LAYOUT_planck_grid(
    LGUI(KC_0),  LGUI(KC_1),  LGUI(KC_2),  LGUI(KC_3),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  LGUI(KC_0),  LGUI(KC_1),  LGUI(KC_2),  LGUI(KC_3),
    _______,     LGUI(KC_4),  LGUI(KC_5),  LGUI(KC_6),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,     LGUI(KC_4),  LGUI(KC_5),  LGUI(KC_6),
    _______,     LGUI(KC_7),  LGUI(KC_8),  LGUI(KC_9),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,     LGUI(KC_7),  LGUI(KC_8),  LGUI(KC_9),
    _______,     _______,     _______,     XXXXXXX,     XXXXXXX,  XXXXXXX,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX
  ),

  [_FUNCTION] = LAYOUT_planck_grid(
    _______,  KC_F1,   KC_F2,   KC_F3,   XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_F1,   KC_F2,   KC_F3,
    _______,  KC_F4,   KC_F5,   KC_F6,   XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_F4,   KC_F5,   KC_F6,
    _______,  KC_F7,   KC_F8,   KC_F9,   XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_F7,   KC_F8,   KC_F9,
    _______,  KC_F10,  KC_F11,  KC_F12,  XXXXXXX,  XXXXXXX,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_F10,  KC_F11,  KC_F12
  ),

  [_ADJUST] = LAYOUT_planck_grid(
    _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  AU_ON,    AU_OFF,   AU_TOG,   _______,    _______,  _______,  _______,  _______,  _______,  RESET,
    _______,  _______,  MU_ON,    MU_OFF,   MU_TOG,   _______,    _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,/**/XXXXXXX,  _______,  _______,  _______,  _______,  _______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}

// define raise/lower layers so template code below works unchanged
#define _LOWER _NAV
#define _RAISE _SYMBOLS
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
