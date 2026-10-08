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
#include "raw_hid.h"

// Home row mods (comme le Cornifi, keymap mimi_qwerty) sur les couches de base
// Mac et Win : A S D F = GUI Alt Shift Ctrl, J K L ; = Ctrl Shift Alt GUI.
// Maintenir = modificateur, taper = lettre (TAPPING_TERM par défaut : 200 ms).
// Caps Lock : tap = Échap, maintien = Ctrl (comme la config kanata).
// Les deux Shift ensemble = Caps Word (remplace le Verr. Maj).
// Couches Fn : J reste un vrai KC_J, sinon le reset usine Keychron
// (Fn + J + Z, qui attend KC_J) ne voit pas la touche.

// clang-format off
enum layers{
  MAC_BASE,
  MAC_FN,
  WIN_BASE,
  WIN_FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_SNAP,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,     KC_H,     LCTL_T(KC_J), LSFT_T(KC_K), LALT_T(KC_L), LGUI_T(KC_SCLN), KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                                 KC_RCMMD,MO(MAC_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[MAC_FN] = LAYOUT_ansi_84(
     KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_J,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_BASE] = LAYOUT_ansi_84(
     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_PSCR,  KC_DEL,   RGB_MOD,
     KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
     LCTL_T(KC_ESC), LGUI_T(KC_A), LALT_T(KC_S), LSFT_T(KC_D), LCTL_T(KC_F), KC_G,     KC_H,     LCTL_T(KC_J), LSFT_T(KC_K), LALT_T(KC_L), LGUI_T(KC_SCLN), KC_QUOT,            KC_ENT,             KC_HOME,
     KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,  KC_UP,    KC_END,
     KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT, MO(WIN_FN),KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

[WIN_FN] = LAYOUT_ansi_84(
     KC_TRNS,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_J,     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,            KC_TRNS,
     KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  BAT_LVL,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                                KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_ESC):
            return 100;
        default:
            return TAPPING_TERM;
    }
}

// Raw HID : la couche et les modificateurs actifs sont envoyés à l'ordinateur
// (indicateur Waybar, ~/.config/waybar/scripts/cornifi-layer), même protocole
// que le Cornifi. Message de 32 octets : { RAW_LAYER_MSG, numéro de couche
// (enum layers), modificateurs (get_mods(), octet HID : bits 0-3 Ctrl/Shift/
// Alt/GUI gauches, bits 4-7 droits), 0… }.
// L'ordinateur peut aussi envoyer { RAW_LAYER_MSG } pour demander la couche.
#define RAW_LAYER_MSG 0x4C // 'L'

// L'ordinateur interroge le clavier chaque seconde ; on n'envoie que s'il l'a
// fait récemment : sans lecteur, raw_hid_send bloquerait jusqu'à 100 ms une
// fois la file USB pleine (ressenti à chaque changement de couche).
#define RAW_HOST_TIMEOUT 3000 // ms

static uint32_t raw_host_seen   = 0;
static bool     raw_host_active = false;

static void send_state(layer_state_t state) {
    if (!raw_host_active || timer_elapsed32(raw_host_seen) > RAW_HOST_TIMEOUT) {
        raw_host_active = false;
        return;
    }
    uint8_t data[32] = {RAW_LAYER_MSG, get_highest_layer(state | default_layer_state), get_mods()}; // 32 = RAW_EPSIZE (USB)
    raw_hid_send(data, sizeof(data));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    send_state(state);
    return state;
}

// appelée en continu : envoie les changements de modificateurs (home row mods
// maintenus, Ctrl du Caps Lock, vrais modificateurs)
void housekeeping_task_user(void) {
    static uint8_t last_mods = 0;
    uint8_t        mods      = get_mods();
    if (mods != last_mods) {
        last_mods = mods;
        send_state(layer_state);
    }
}

void raw_hid_receive_k3pro(uint8_t *data, uint8_t length); // k3_pro.c, renommée (rules.mk)

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 0 && data[0] == RAW_LAYER_MSG) {
        raw_host_active = true;
        raw_host_seen   = timer_read32();
        send_state(layer_state);
        return;
    }
    raw_hid_receive_k3pro(data, length);
}
