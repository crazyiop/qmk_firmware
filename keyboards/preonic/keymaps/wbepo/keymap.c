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

#include "led.c"

#define _______ KC_TRNS
#define xxxxxxx KC_NO

// keymaps
enum layers {
  BEPO = 0,
  RAISE,
  LOWER,
  RISE,
  DROP,
};

// custom keycode, for macro
enum custom_keycodes {
  COPY = SAFE_RANGE, // can always be here
  PASTE,
  CUT,
  SHIFT,
  CAPSLOCK,
  ALT_TAB,
  LED,
};

static bool capslock_on = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BEPO] = {
    {BP_DLR,   BP_DQOT, KC_PERC,  KC_ESC,    BP_LPRN, BP_RPRN,        BP_AT,       BP_PLUS, BP_MINS,   BP_SLSH, BP_ASTR, BP_EQL},
    {KC_TAB,   BP_B,    BP_ECUT,  BP_P,      BP_O,    BP_GRV,         BP_DCRC,     BP_V,    BP_D,      BP_L,    BP_J,    BP_Z},
    {BP_W,     BP_A,    BP_U,     BP_I,      BP_E,    SFT_T(BP_COMM), SFT_T(BP_C), BP_T,    BP_S,      BP_R,    BP_N,    BP_M},
    {KC_LCTRL, BP_Z,    BP_Y,     BP_X,      BP_DOT,  BP_K,           BP_APOS,     BP_Q,    BP_G,      BP_H,    BP_F,    KC_RCTL},
    {COPY,     PASTE,   MO(DROP), MO(LOWER), KC_BSPC, KC_DEL,         KC_ENT,      KC_SPC,  MO(RAISE), MO(RISE),  xxxxxxx, BP_CCED},
  },

  [RAISE] = {
    {_______, _______, BP_LESS, BP_GRTR, _______, _______, _______, BP_PSMS, BP_MMNS, BP_OBEL, BP_DVSN, BP_DIFF},
    {ALT_TAB, BP_PIPE, BP_LBRC, BP_RBRC, _______, BP_DGRV, _______, _______, _______, _______, _______, _______},
    {KC_BTN3, BP_AMPR, BP_LPRN, BP_RPRN, BP_EURO, _______, BP_CCED, _______, _______, _______, _______, _______},
    {_______, BP_BSLS, BP_LCBR, BP_RCBR, BP_UNDS, BP_TILD, _______, _______, BP_DGRK, _______, _______, _______},
    {_______, _______, _______, _______, _______, KC_DEL,  KC_BSPC, _______, _______, _______, _______, _______},
  },


  [LOWER] = {
    {_______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,    _______, _______},
    {ALT_TAB, _______, BP_DACT, _______, BP_OE,   _______, _______, RCTL(BP_B), KC_UP,   RCTL(BP_W), _______, _______},
    {_______, BP_AE,   BP_UGRV, BP_DTRM, _______, BP_TAPO, _______, KC_LEFT,    KC_DOWN, KC_RGHT,    _______, CAPSLOCK},
    {_______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,    _______, _______},
    {_______, _______, _______, _______, _______, KC_DEL,  KC_BSPC, _______,    _______, _______,    _______, _______},
  },

  [RISE] = {
    {_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11},
    {_______, _______, BP_EGRV, KC_PGDN, _______, _______, _______, _______, _______, _______, _______, KC_F12},
    {_______, BP_AGRV, KC_HOME, KC_PGUP, KC_END,  _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  },

  [DROP] = {
    {_______, LED,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_7), S(KC_8), S(KC_9), _______, KC_TAB },
    {_______, _______, _______, _______, _______, _______, _______, S(KC_4), S(KC_5), S(KC_6), _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_1), S(KC_2), S(KC_3), _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, S(KC_0), BP_DOT,  BP_COMM, _______, _______},
  },

  /* model for new layer
  [BLANK] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______},
  },
  */
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
  // uint8_t layer = biton32(layer_state);

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

    case ALT_TAB:
      if (record->event.pressed) {
        SEND_STRING(SS_LALT(SS_TAP(X_TAB)));
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
    case LED:
      if (record->event.pressed) {
        led_level++;
        led_level %= LED_LEVEL;
      }
      break;
  }

  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
   _delay_ms(20);
  rgblight_enable();
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
    rgball(NONE);
    break;
  case LOWER:
    rgball(BLUE);
    break;
  case RAISE:
    rgball(RED);
    break;
  case RISE:
    rgball(YELLOW);
    break;
  case DROP:
    rgball(GREEN);
    break;
  default:
    // none
    break;
  }
};
