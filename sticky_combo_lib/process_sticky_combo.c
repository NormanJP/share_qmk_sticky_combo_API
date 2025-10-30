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

#include "process_sticky_combo.h"

uint8_t most_recently_visited_base_layer = LAYER_UNSET;
uint8_t current_layer = LAYER_UNSET;
bool base_layer_on = false;

void refresh_sticky_combo_globals() {
    current_layer = biton32(layer_state);
    base_layer_on = is_base_layer_on();
    if (base_layer_on) {
        most_recently_visited_base_layer = current_layer;
    }
}

bool is_base_layer_on() {
    for (uint8_t layer_index = 0;
         layer_index < user_defined_base_layers_length;
         layer_index++) {
        if (user_defined_base_layers[layer_index] == current_layer) {
            return true;
        }
    }
    return false;
}

bool turn_on_appropriate_layer_and_report_if_layer_changed(uint16_t pressed_keycode) {
    if (!base_layer_on) return false;
    FOR_EACH_USER_DEFINED_STICKY_COMBO_RULE()
        const uint8_t sticky_layer = user_defined_sticky_combo_rule.layer;
        const uint16_t sticky_key = user_defined_sticky_combo_rule.sticky_key;
        const uint16_t trigger = user_defined_sticky_combo_rule.layer_trigger_button;
        const uint16_t *extended_combo_keys = user_defined_sticky_combo_rule
            .optional_extended_combo_key_list;
        const uint8_t extended_combo_keys_length = user_defined_sticky_combo_rule
                .optional_extended_combo_key_list_length;

        if (trigger == pressed_keycode
            && is_mod_pressed(sticky_key)
            && extended_combo_keys_pressed(extended_combo_keys,
                                           extended_combo_keys_length)
        ) {
            unregister_code(trigger);
            unregister_code(sticky_key);
            unregister_codes(extended_combo_keys, extended_combo_keys_length);
            layer_move(sticky_layer);
            return true;
        }
    END_FOR()
    return false;
}

void return_to_base_layer() {
    uint8_t base_layer = determine_base_layer();
    layer_move(base_layer);
}

bool key_up_for_current_layer_end_is_signaled_by(uint16_t keycode) {
    return !base_layer_on
        && sticky_key_for_current_layer_is(keycode);
}

void unregister_codes(const uint16_t key_codes[], const uint8_t length) {
    for (uint8_t key_index = 0;
         key_index < length;
         key_index++) {
        const uint16_t key = key_codes[key_index];
        unregister_code(key);
    }
}

bool extended_combo_keys_pressed(const uint16_t extended_combo_keys[], const uint8_t length) {
    for (uint8_t combo_key_index = 0;
         combo_key_index < length;
         combo_key_index++) {
        const uint16_t combo_key = extended_combo_keys[combo_key_index];
        if (!is_mod_pressed(combo_key)) return false;
    }
    return true;
}

bool is_mod_pressed(uint16_t keycode) {
    return get_mods() & MOD_BIT(keycode);
}

bool sticky_key_for_current_layer_is(uint16_t keycode) {
    FOR_EACH_USER_DEFINED_STICKY_COMBO_RULE()
        if (user_defined_sticky_combo_rule.layer == current_layer
            && user_defined_sticky_combo_rule.sticky_key == keycode) {
            return true;
        }
    END_FOR()
    return false;
}

uint8_t determine_base_layer() {
    if (most_recently_visited_base_layer != LAYER_UNSET) {
        return most_recently_visited_base_layer;
    }

    return user_defined_base_layers[0];
}

bool process_record_sticky_combo(uint16_t keycode, keyrecord_t *record) {
    refresh_sticky_combo_globals();

    if (record->event.pressed) {
        return !turn_on_appropriate_layer_and_report_if_layer_changed(keycode);
    } else if (!record->event.pressed
               && key_up_for_current_layer_end_is_signaled_by(keycode)) {
        return_to_base_layer();
    }

    return true;
}
