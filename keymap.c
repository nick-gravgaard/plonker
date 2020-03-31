#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "keymap_uk.h"



typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  DOUBLE_SINGLE_TAP, //send two single taps
  TRIPLE_TAP,
  TRIPLE_HOLD,
  PAST_TRIPLE
};

//Tap dance enums
enum {
  TD_ESCAPE_OR_NAV = 0,
  TD_LB,
  TD_RB
};

int cur_dance (qk_tap_dance_state_t *state);

//for the bracket tap dances. Placed here so they can be used in any keymap
void lb_finished (qk_tap_dance_state_t *state, void *user_data);
void lb_reset (qk_tap_dance_state_t *state, void *user_data);
void rb_finished (qk_tap_dance_state_t *state, void *user_data);
void rb_reset (qk_tap_dance_state_t *state, void *user_data);



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
  _MOVE,
  _FUNCTION,
  _ADJUST,
};


#define ESCAPE_OR_NAV   TD(TD_ESCAPE_OR_NAV)
#define SPACE_OR_NAV    LT(_NAV, KC_SPACE)
#define TAB_OR_SYMBOLS  LT(_SYMBOLS, KC_TAB)
#define F_OR_FUNCTION   LT(_FUNCTION, KC_F)
#define J_OR_JUMP       LT(_JUMP, KC_J)
#define M_OR_MOVE       LT(_MOVE, KC_M)
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

#define L_ROUND_BRACKET_UNSHIFTED     KC_9
#define R_ROUND_BRACKET_UNSHIFTED     KC_0
#define L_SQUIGGLY_BRACKET_UNSHIFTED  KC_LBRACKET
#define R_SQUIGGLY_BRACKET_UNSHIFTED  KC_RBRACKET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_planck_grid(
    ESCAPE_OR_NAV,   KC_Q,     KC_W,     KC_E,      KC_R,          KC_T,            KC_Y,          KC_U,       KC_I,       KC_O,     P_OR_DEL,   KC_BSPACE,
    TAB_OR_SYMBOLS,  KC_A,     KC_S,     KC_D,      F_OR_FUNCTION, KC_G,            KC_H,          J_OR_JUMP,  KC_K,       KC_L,     KC_SCOLON,  UK_QUOT,
    SHIFT_LAYER,     KC_Z,     KC_X,     KC_C,      KC_V,          KC_B,            N_OR_NUMBERS,  M_OR_MOVE,  KC_COMMA,   KC_DOT,   KC_UP,      KC_ENTER,
    KC_LCTRL,        KC_LGUI,  KC_LALT,  KC_MINUS,  KC_EQUAL,      SPACE_OR_NAV,/**/XXXXXXX,       TD(TD_LB),  TD(TD_RB),  KC_LEFT,  KC_DOWN,    KC_RIGHT
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
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,
    _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PGUP,    XXXXXXX,
    _______,  _______,  _______,  XXXXXXX,  XXXXXXX,  _______,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_HOME,  KC_PGDOWN,  KC_END
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

  [_MOVE] = LAYOUT_planck_grid(
    LSFT(LGUI(KC_0)),  LSFT(LGUI(KC_1)),  LSFT(LGUI(KC_2)),  LSFT(LGUI(KC_3)),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  LSFT(LGUI(KC_0)),  LSFT(LGUI(KC_1)),  LSFT(LGUI(KC_2)),  LSFT(LGUI(KC_3)),
    _______,           LSFT(LGUI(KC_4)),  LSFT(LGUI(KC_5)),  LSFT(LGUI(KC_6)),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,           LSFT(LGUI(KC_4)),  LSFT(LGUI(KC_5)),  LSFT(LGUI(KC_6)),
    _______,           LSFT(LGUI(KC_7)),  LSFT(LGUI(KC_8)),  LSFT(LGUI(KC_9)),  XXXXXXX,  XXXXXXX,    XXXXXXX,  XXXXXXX,  XXXXXXX,           LSFT(LGUI(KC_7)),  LSFT(LGUI(KC_8)),  LSFT(LGUI(KC_9)),
    _______,           _______,           _______,           XXXXXXX,           XXXXXXX,  XXXXXXX,/**/XXXXXXX,  XXXXXXX,  XXXXXXX,           XXXXXXX,           XXXXXXX,           XXXXXXX
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



// code from https://docs.qmk.fm/#/feature_tap_dance?id=example-4-quad-function-tap-dance

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return PAST_TRIPLE; //magic number. At some point this method will expand to work for more presses
}

//instantialise an instance of 'tap' for the 'lb' (left bracket) tap dance.
static tap lbtap_state = {
  .is_press_action = true,
  .state = 0
};

void lb_finished (qk_tap_dance_state_t *state, void *user_data) {
  lbtap_state.state = cur_dance(state);
  switch (lbtap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(L_ROUND_BRACKET_UNSHIFTED); break;
    case DOUBLE_TAP: register_code(L_SQUARE_BRACKET); break;
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(L_SQUIGGLY_BRACKET_UNSHIFTED); break;
    //case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void lb_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lbtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(L_ROUND_BRACKET_UNSHIFTED); break;
    case DOUBLE_TAP: unregister_code(L_SQUARE_BRACKET); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(L_SQUIGGLY_BRACKET_UNSHIFTED); break;
    //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  lbtap_state.state = 0;
}

//instantialise an instance of 'tap' for the 'rb' (right bracket) tap dance.
static tap rbtap_state = {
  .is_press_action = true,
  .state = 0
};

void rb_finished (qk_tap_dance_state_t *state, void *user_data) {
  rbtap_state.state = cur_dance(state);
  switch (rbtap_state.state) {
    case SINGLE_TAP: register_code(KC_LSFT); register_code(R_ROUND_BRACKET_UNSHIFTED); break;
    case SINGLE_HOLD: layer_on(_NAV); break;
    case DOUBLE_TAP: register_code(R_SQUARE_BRACKET); break;
    case TRIPLE_TAP: register_code(KC_LSFT); register_code(R_SQUIGGLY_BRACKET_UNSHIFTED); break;
    //case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    //Last case is for fast typing. Assuming your key is `f`:
    //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
    //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
  }
}

void rb_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rbtap_state.state) {
    case SINGLE_TAP: unregister_code(KC_LSFT); unregister_code(R_ROUND_BRACKET_UNSHIFTED); break;
    case SINGLE_HOLD: layer_off(_NAV); break;
    case DOUBLE_TAP: unregister_code(R_SQUARE_BRACKET); break;
    case TRIPLE_TAP: unregister_code(KC_LSFT); unregister_code(R_SQUIGGLY_BRACKET_UNSHIFTED); break;
    //case DOUBLE_SINGLE_TAP: unregister_code(KC_X);
  }
  rbtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_ESCAPE_OR_NAV] = ACTION_TAP_DANCE_LAYER_MOVE(KC_ESCAPE, _NAV),
  [TD_LB]            = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lb_finished, lb_reset),
  [TD_RB]            = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rb_finished, rb_reset)
};
