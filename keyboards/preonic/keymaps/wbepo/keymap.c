/* Copyright 2015-2017 Jack Humbert
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

#include "preonic.h"
#include "action_layer.h"
#include "keymap_bepo.h"
#include <sendstring_bepo.h>

#define _______ KC_TRNS
#define xxxxxxx KC_NO

// keymaps
enum layers {
  BEPO = 0,
  NUM,
  UTILITY,
  ALT_GR,
  BLANK,
};

// custom keycode, for macro
enum custom_keycodes {
  COPY = SAFE_RANGE, // can always be here
  PASTE,
  CUT,
  SHIFT,
  CAPSLOCK,
};

static bool capslock_on = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BEPO] = {
    {BP_DLR,   BP_DQOT,  BP_LGIL, BP_RGIL,     BP_LPRN,      BP_RPRN, BP_AT,   BP_PLUS,     BP_MINS,     BP_SLSH, BP_ASTR, BP_EQL},
    {KC_TAB,   BP_B,     BP_ECUT, BP_P,        BP_O,         BP_EGRV, BP_DCRC, BP_V,        BP_D,        BP_L,    BP_J,    BP_Z},
    {BP_W,     BP_A,     BP_U,    BP_I,        SFT_T(BP_E),  BP_COMM, BP_C,    SFT_T(BP_T), BP_S,        BP_R,        BP_N,    BP_M},
    {KC_LCTRL, BP_AGRV,  BP_Y,    BP_X,        BP_DOT,       BP_K,    BP_APOS, BP_Q,        BP_G,        BP_H,    BP_F,    KC_RCTL},
    {COPY,     PASTE,    CUT,     MO(UTILITY), KC_LALT,      KC_BSPC, KC_SPC,  KC_RALT,     MO(UTILITY), xxxxxxx, xxxxxxx,  BP_CCED},
  },

  [BLANK] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  },

  [UTILITY] = {
    {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,   KC_F7,      KC_F8,    KC_F9,      KC_F10,  KC_F11},
    {_______, _______, KC_PGDN, KC_UP,   KC_PGUP,  _______, _______, RCTL(BP_B), KC_UP,    RCTL(BP_W), _______, KC_F12},
    {KC_BTN3, _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, KC_LEFT,    KC_DOWN,  KC_RGHT,    _______, CAPSLOCK},
    {_______, _______, _______, _______, _______,  _______, _______, _______,     _______, _______,    _______, _______},
    {_______, _______, _______, _______, _______,  _______, _______, _______,    _______,  _______,    _______, _______},
  },

  [ALT_GR] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  },

  [NUM] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_7), S(KC_8), S(KC_9), _______, KC_TAB },
    {_______, _______, _______, _______, _______, _______, _______, S(KC_4), S(KC_5), S(KC_6), _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_1), S(KC_2), S(KC_3), _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_0), BP_DOT,  BP_COMM, _______, _______},
  },

};

        /*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
       case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
      }
    return true;
};
        */

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  uint8_t layer = biton32(layer_state);

  if (layer == ALT_GR) {
    if ((keycode >= KC_A) && (keycode <= KC_EXSEL)
      // && !((keycode == KC_1) ||
      //    )
       )
    {
      if (record->event.pressed) {
        register_mods(MOD_BIT(KC_RALT));
      } else {
        register_mods(MOD_BIT(KC_RALT));
      }
    }
  } else {
    switch(keycode) {
      case KC_ESC:
        // macro to have escape also desactivating caps lock if active
        if (record->event.pressed) {
          if (capslock_on) {
            SEND_STRING(SS_TAP(X_ESCAPE) SS_TAP(X_CAPSLOCK));
            capslock_on = false;
          } else {
            SEND_STRING(SS_TAP(X_ESCAPE));
          }
          return false;
        }
        break;
      case COPY:
        if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("c"));
          return false;
        }
        break;
      case PASTE:
        if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("v"));
          return false;
        }
        break;
      case CUT:
        if (record->event.pressed) {
          SEND_STRING(SS_LCTRL("x"));
          return false;
        }
        break;
      case SHIFT:
        // macro to activate caps lock if both shift are pressed
        if (record->event.pressed) {
          if (keyboard_report->mods & (MOD_BIT(KC_LSFT))){
            // if shift is already register from the other hand
            // activate caps lock
            unregister_code(KC_LSFT);
            SEND_STRING(SS_TAP(X_CAPSLOCK));
            capslock_on = !capslock_on;
            return false;
          }else{
            // register shift as it is the first hand press
            register_code(KC_LSFT);
          }
        }else{
          unregister_code(KC_LSFT);
        }
        break;
      case CAPSLOCK:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_CAPSLOCK));
          capslock_on = !capslock_on;
          return false;
        }
        break;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs periodicaly (a lot)
void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

  if (capslock_on) {
    //ergodox_right_led_3_on();
  } else {
    //ergodox_right_led_3_off();
  }

  switch (layer) {
  case BEPO:
    //ergodox_right_led_1_off();
    //ergodox_right_led_2_off();
    break;
  case UTILITY:
    //ergodox_right_led_1_on();
    break;
  case NUM:
    //ergodox_right_led_2_on();
    break;
  default:
    // none
    break;
  }
};
