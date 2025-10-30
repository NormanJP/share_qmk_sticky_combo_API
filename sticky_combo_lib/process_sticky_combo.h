// SPDX-License-Identifier: MIT
// Copyright (c) 2025 Norman Paprakis
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND...

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "action.h"
#include QMK_KEYBOARD_H
#include "keychron_common.h"

#define LAYER_UNSET 0xFF
#define MAX_STICKY_KEY_EXTENDED_COMBO_KEY_COUNT 3

typedef struct {
    uint8_t  layer;
    uint16_t sticky_key;
    uint16_t layer_trigger_button;
    uint16_t optional_extended_combo_key_list[MAX_STICKY_KEY_EXTENDED_COMBO_KEY_COUNT];
    uint8_t optional_extended_combo_key_list_length;
} sticky_combo_rule_t;

extern const sticky_combo_rule_t user_defined_sticky_combos[];
extern const uint8_t user_defined_sticky_combos_length;
extern const uint8_t user_defined_base_layers[];
extern const uint8_t user_defined_base_layers_length;

void refresh_sticky_combo_globals(void);
bool is_base_layer_on(void);
bool turn_on_appropriate_layer_and_report_if_layer_changed(uint16_t pressed_keycode);
void return_to_base_layer(void);
bool key_up_for_current_layer_end_is_signaled_by(uint16_t keycode);
void unregister_codes(const uint16_t key_codes[], const uint8_t length);
bool extended_combo_keys_pressed(const uint16_t extended_combo_keys[], const uint8_t length);
bool is_mod_pressed(uint16_t keycode);
bool sticky_key_for_current_layer_is(uint16_t keycode);
uint8_t determine_base_layer(void);
bool process_record_sticky_combo(uint16_t keycode, keyrecord_t *record);

#define FOR_EACH_USER_DEFINED_STICKY_COMBO_RULE() \
    for (uint8_t sticky_combo_rule_index = 0; \
         sticky_combo_rule_index < user_defined_sticky_combos_length; \
         sticky_combo_rule_index++) { \
        const sticky_combo_rule_t user_defined_sticky_combo_rule = user_defined_sticky_combos[sticky_combo_rule_index];

#define END_FOR() }
