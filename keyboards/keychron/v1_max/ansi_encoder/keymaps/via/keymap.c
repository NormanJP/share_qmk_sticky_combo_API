/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "keymap.h"
#include "keychron_common.h"
#include "print.h"
#include "send_string.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "process_sticky_combo.h"

enum custom_keycodes {
    KC_STICKY_HOLDER = SAFE_RANGE
};

enum abbreviated_custom_keycodes {
    KC_STH_ = KC_STICKY_HOLDER
};

// Mouse key speed and acceleration. From another project
#undef  MOUSEKEY_DELAY
#define MOUSEKEY_DELAY          0
#undef  MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL       16
#undef  MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY    0
#undef  MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED      6
#undef  MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX    64

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
    UNIVERSAL_EXTRA_LAYER_1,
    UNIVERSAL_EXTRA_LAYER_2,
    UNIVERSAL_EXTRA_LAYER_3,
    UNIVERSAL_EXTRA_LAYER_4
};
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_82(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  MO(MAC_BASE)),

    [WIN_BASE] = LAYOUT_ansi_82(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_82(
        _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,            RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  KC_MS_BTN1,  KC_MS_UP,  KC_MS_BTN2,  _______,  _______,  _______,  _______,            _______,
        _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  _______,  KC_MS_LEFT,  KC_MS_DOWN,  KC_MS_RIGHT,  _______,  _______,            _______,            KC_END,
        _______,            _______,  _______,  _______,  _______,  BAT_LVL,  NK_TOGG,  KC_MS_ACCEL0,  KC_MS_ACCEL2,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                KC_MS_ACCEL1,                                _______,  _______,  _______,  _______,  _______,  MO(WIN_BASE)),

    // KC_LCTL + KC_SPC
    [UNIVERSAL_EXTRA_LAYER_1] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_ESC,   S(KC_GRV),KC_SLSH,  S(KC_EQL),KC_T,     KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_NO,    KC_EQL,   KC_GRV,   KC_RCTL,  KC_LSFT,  KC_G,     KC_H,     KC_4,     KC_5,     KC_6,     KC_BSPC,  KC_DEL,             KC_ENT,             KC_HOME,
        KC_LSFT,            KC_QUOT,  S(KC_QUOT),KC_MINS, S(KC_MINS),KC_CAPS, S(KC_COMM),  KC_1,     KC_2,     KC_3,     KC_DEL,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_0,     TO(WIN_BASE),KC_RCTL,KC_LEFT, KC_DOWN,  KC_RGHT),

    // My Mouse Layer
    // KC_LSFT + KC_SPC
    [UNIVERSAL_EXTRA_LAYER_2] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,    KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,       KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_ESC,   KC_BTN4,  KC_BTN5,  KC_R,     KC_T,     KC_Y,     KC_WH_D,    KC_MS_UP, KC_WH_U,  KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_LCTL,  KC_BTN1,  KC_BTN3,  KC_BTN2,  KC_F,     KC_G,     KC_WH_L,  KC_MS_LEFT, KC_MS_DOWN,KC_MS_RIGHT,KC_WH_R,KC_QUOT,           KC_ENT,             KC_HOME,
        KC_NO,    KC_BTN6,  KC_BTN7,  KC_BTN8,  KC_V,     KC_B,     KC_MS_ACCEL2,KC_MS_ACCEL1,KC_COMM,KC_DOT, KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_MS_ACCEL0,                                  KC_RCMMD,TO(WIN_BASE),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    // KC_LCTL + KC_LCMMD/L_ALT + KC_SPC
    [UNIVERSAL_EXTRA_LAYER_3] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_ESC,   S(KC_GRV),KC_SLSH,  S(KC_EQL),KC_T,     KC_EQL,   KC_BSPC,  KC_UP,    KC_END,   KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_STH_,  KC_EQL,   KC_GRV,   KC_RCTL,  KC_LSFT,  KC_G,     KC_H,     KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_LSFT,            KC_QUOT,  S(KC_QUOT),KC_MINS, S(KC_MINS),KC_B,    KC_MINS,  KC_EQL,   KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_NO,                                  KC_SPC + 1,                                  KC_RCMMD,TO(WIN_BASE),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    // KC_RSFT + KC_SPC
    [UNIVERSAL_EXTRA_LAYER_4] = LAYOUT_ansi_82(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_ESC,   S(KC_GRV),KC_SLSH,  S(KC_EQL),KC_T,     KC_EQL,   KC_7,     KC_8,     KC_9,     KC_0,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_NO,    KC_EQL,   KC_GRV,   KC_RCTL,  KC_LSFT,  KC_G,     KC_H,     KC_4,     KC_5,     KC_6,     KC_BSPC,  KC_DEL,             KC_ENT,             KC_HOME,
        KC_LSFT,            KC_QUOT,  S(KC_QUOT),KC_MINS, S(KC_MINS),KC_CAPS, S(KC_COMM),  KC_1,     KC_2,     KC_3,     KC_DEL,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_0,     TO(WIN_BASE),KC_RCTL,KC_LEFT, KC_DOWN,  KC_RGHT)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [UNIVERSAL_EXTRA_LAYER_1]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [UNIVERSAL_EXTRA_LAYER_2]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [UNIVERSAL_EXTRA_LAYER_3]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [UNIVERSAL_EXTRA_LAYER_4]   = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},

};
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    const bool keychron_common_result = process_record_keychron_common(keycode, record);
    const bool sticky_combo_result = process_record_sticky_combo(keycode, record);
    return keychron_common_result && sticky_combo_result;
}

const sticky_combo_rule_t user_defined_sticky_combos[] = { 
    /*{            LAYER_NAME, STCKYKEY, TRIGGR, {EXTRAMODS}, XMODLEN}*/
    { UNIVERSAL_EXTRA_LAYER_3,  KC_LCTL, KC_SPC, { KC_LALT }, 1 },
    { UNIVERSAL_EXTRA_LAYER_3,  KC_LCTL, KC_SPC, { KC_LCMMD }, 1 },
    { UNIVERSAL_EXTRA_LAYER_1,  KC_LCTL, KC_SPC, { }, 0 },
    { UNIVERSAL_EXTRA_LAYER_2,  KC_LSFT, KC_SPC, { }, 0 },
    { UNIVERSAL_EXTRA_LAYER_4,  KC_RSFT, KC_SPC, { }, 0 },
};
const uint8_t user_defined_sticky_combos_length = 5;

const uint8_t user_defined_base_layers[] = { WIN_BASE, MAC_BASE };
const uint8_t user_defined_base_layers_length = 2;