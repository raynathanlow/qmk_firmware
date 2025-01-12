/* Copyright 2015-2021 Jack Humbert
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

#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _SPECIAL,
  _LOWER,
  _RAISE,
  _PLOVER,
  _ADJUST,
  _SWAPPER
};

enum planck_keycodes {
    ALT_TAB = SAFE_RANGE,
};

#define SPECIAL OSL(_SPECIAL)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define QWERTY PDF(_QWERTY)

#define SCRSHT1 LT(0, KC_A)
#define SCRSHT2 LT(0, KC_B)
#define SCRSHT3 LT(0, KC_C)
#define REFRESH LT(0, KC_D)
#define DUPE LT(0, KC_E)
#define CLOSE LT(0, KC_F)
#define PGUP LT(0, KC_G)
#define PGDN LT(0, KC_H)

bool is_alt_tab_active = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,    KC_TRNS, KC_TRNS, KC_Y,   KC_U,         KC_I,         KC_O,         KC_P,
    LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F), KC_G,    KC_TRNS, KC_TRNS, KC_H,   RSFT_T(KC_J), RCTL_T(KC_K), LALT_T(KC_L), RGUI_T(KC_SCLN),
    KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,    KC_TRNS, KC_TRNS, KC_N,   KC_M,         KC_COMM,      KC_DOT,       KC_SLSH,
    KC_TRNS,      KC_TRNS,      SPECIAL,      KC_BSPC,      LOWER, KC_TRNS, KC_TRNS, RAISE,  KC_SPC,        KC_DEL,      KC_TRNS,      KC_TRNS
),

[_SPECIAL] = LAYOUT_planck_grid(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    LGUI_T(KC_1),     LALT_T(KC_2),    LCTL_T(KC_3),    LSFT_T(KC_4),    KC_5,    KC_TRNS, KC_TRNS, RSFT_T(KC_6),    RCTL_T(KC_7),    LALT_T(KC_8),    RGUI_T(KC_9),    KC_0,
    CLOSE,   DUPE,    REFRESH, KC_GRV,  KC_BSLS, KC_TRNS, KC_TRNS, KC_EQL,  KC_QUOT, KC_MINS, KC_LBRC, KC_RBRC,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_LOWER] = LAYOUT_planck_grid(
    KC_TRNS, SCRSHT3, SCRSHT2, SCRSHT1, PGUP,    KC_TRNS, KC_TRNS, KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, PGDN,    KC_TRNS, KC_TRNS, CW_TOGG, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y), KC_TRNS, KC_TRNS, KC_TRNS, KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, KC_ESC,  S(KC_TAB), KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_MPRV,
    KC_LGUI, KC_LALT, KC_LCTL,   KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_LEFT, KC_DOWN, KC_RGHT, KC_MNXT,
    KC_TRNS, KC_TRNS, KC_TRNS,   KC_SCRL, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_BSPC, KC_DEL,  KC_ENT,  KC_APP,
    KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_SWAPPER] = LAYOUT_planck_grid(
     _______, KC_ESC,  KC_UP,   KC_DEL,   _______, _______, _______, _______, _______, _______, _______, _______,
     _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______,  ALT_TAB, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, UG_TOGG, UG_NEXT, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool is_swapper_ignored_key(uint16_t keycode) {
    switch (keycode) {
        case KC_UP:
        case KC_LEFT:
        case KC_DOWN:
        case KC_RGHT:
        case KC_DEL:
            return true;
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
if (keycode == ALT_TAB) {
    if (record->event.pressed) {
        if (!is_alt_tab_active) {
            is_alt_tab_active = true;
            register_code(KC_LALT);
            layer_on(_SWAPPER);
        }
        register_code(KC_TAB);
        } else {
        unregister_code(KC_TAB);
        }
} else if (is_alt_tab_active && !is_swapper_ignored_key(keycode)) {
    unregister_code(KC_LALT);
    is_alt_tab_active = false;
    layer_off(_SWAPPER);
    return false;
}

  switch (keycode) {
      case SCRSHT1:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(KC_PSCR));
          } else if (record->event.pressed) {
              tap_code16(S(KC_PSCR));
          }
          return false;
          break;
      case SCRSHT2:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(S(KC_PSCR)));
          } else if (record->event.pressed) {
              tap_code16(A(KC_PSCR));
          }
          return false;
          break;
      case SCRSHT3:
          if (record->tap.count && record->event.pressed) {
              tap_code16(A(S(KC_PSCR)));
          } else if (record->event.pressed) {
              tap_code16(KC_PSCR);
          }
          return false;
          break;
      case REFRESH:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(KC_R));
          } else if (record->event.pressed) {
              tap_code16(C(S(KC_R)));
          }
          return false;
          break;
      case DUPE:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(S(KC_K)));
          } else if (record->event.pressed) {
              tap_code16(C(A(KC_K)));
          }
          return false;
          break;
      case CLOSE:
          if (record->tap.count && record->event.pressed) {
              tap_code16(C(KC_W));
          } else if (record->event.pressed) {
              tap_code16(A(KC_F4));
          }
          return false;
          break;
      case PGUP:
          if (record->tap.count && record->event.pressed) {
              tap_code16(KC_PGUP);
          } else if (record->event.pressed) {
              tap_code16(KC_HOME);
          }
          return false;
          break;
      case PGDN:
          if (record->tap.count && record->event.pressed) {
              tap_code16(KC_PGDN);
          } else if (record->event.pressed) {
              tap_code16(KC_END);
          }
          return false;
          break;
  }
  return true;
}

const uint16_t PROGMEM test_combo1[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_M, RSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM test_combo3[] = {KC_R, LSFT_T(KC_F), COMBO_END};
const uint16_t PROGMEM test_combo4[] = {KC_V, LSFT_T(KC_F), COMBO_END};

combo_t key_combos[] = {
    COMBO(test_combo1, KC_ESC),
    COMBO(test_combo2, KC_ENT),
    COMBO(test_combo3, ALT_TAB),
    COMBO(test_combo4, KC_TAB),
};
