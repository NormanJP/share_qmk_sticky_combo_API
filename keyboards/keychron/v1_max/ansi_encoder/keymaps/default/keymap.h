#include QMK_KEYBOARD_H
#include "keychron_common.h"

layer_state_t layer_state_set_user(layer_state_t state);
bool is_mod_pressed(uint16_t keycode);
bool is_base_layer_on(void);
void turn_off_all_mod_layers(void);
bool process_record_custom_behaviours(uint16_t keycode, keyrecord_t *record);
bool turn_on_appropriate_layer_and_report_if_layer_changed(void);
bool suspect_layers_include_current(uint8_t array[], int len, int current);
void return_to_base_layer(void);
bool not_in_base_layer(void);
bool is_sticky_key_for_current_layer(uint16_t keycode);