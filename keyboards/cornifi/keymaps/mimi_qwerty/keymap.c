// Copyright 2025 @v3lmx
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include "raw_hid.h"

enum layer_names {
    _BASE,
    _NAV,
    _ACC,
    _MEDIA,
    _NUM,
    _SYM,
    _FUN,
};

#define U_BASE MO(_BASE)
#define U_NAV MO(_NAV)
#define U_ACC MO(_ACC)
#define U_MEDIA MO(_MEDIA)
#define U_NUM MO(_NUM)
#define U_SYM MO(_SYM)
#define U_FUN MO(_FUN)

// Linux : raccourcis Ctrl classiques (KC_COPY/KC_PSTE… sont ignorés par la
// plupart des applications et par tous les terminaux)
#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

// Raw HID : la couche et les modificateurs actifs sont envoyés à l'ordinateur
// (indicateur Waybar, ~/.config/waybar/scripts/cornifi-layer). Message de
// 32 octets : { RAW_LAYER_MSG, numéro de couche (enum layer_names),
// modificateurs (get_mods(), octet HID : bits 0-3 Ctrl/Shift/Alt/GUI gauches,
// bits 4-7 droits), 0… }.
// L'ordinateur peut aussi envoyer { RAW_LAYER_MSG } pour demander la couche.
#define RAW_LAYER_MSG 0x4C // 'L'

// Tap Dance
enum {
    TD_BOOT,
};

enum accent_keycodes {
    A_AIG = SAFE_RANGE,
    A_GRV,
    A_TRM,
    A_CIR,
    E_AIG,
    E_GRV,
    E_TRM,
    E_CIR,
    I_AIG,
    I_GRV,
    I_TRM,
    I_CIR,
    O_AIG,
    O_GRV,
    O_TRM,
    O_CIR,
    U_AIG,
    U_GRV,
    U_TRM,
    U_CIR,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_BOOT] = ACTION_TAP_DANCE_DOUBLE(KC_NO, QK_BOOT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // clang-format off
    [_BASE] = LAYOUT_split_3x5_3_ex2( // BASE
KC_Q,           KC_W,               KC_E,           KC_R,               KC_T,   KC_NO,          KC_NO,  KC_Y,       KC_U,           KC_I,           KC_O,           KC_P,        \
LGUI_T(KC_A),   LALT_T(KC_S),       LCTL_T(KC_D),   LSFT_T(KC_F),       KC_G,   KC_NO,          KC_NO,  KC_H,       LSFT_T(KC_J),   LCTL_T(KC_K),   LALT_T(KC_L),   LGUI_T(KC_SCLN),   \
KC_Z,           ALGR_T(KC_X),       KC_C,           KC_V,               KC_B,                           KC_N,       KC_M,           KC_COMM,        ALGR_T(KC_DOT), KC_SLSH,        \
                        LT(U_MEDIA,KC_ESC), LT(U_NAV,KC_SPC), LT(U_ACC,KC_TAB),                   LT(U_SYM,KC_ENT), LT(U_NUM,KC_BSPC), LT(U_FUN,KC_DEL)
    ),

    [_NAV] = LAYOUT_split_3x5_3_ex2( // NAV
TD(TD_BOOT),    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,  U_RDO,          U_PST,      U_CPY,      U_CUT,      U_UND,          \
KC_LGUI,        KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,      KC_NO,          KC_NO,  KC_LEFT,        KC_DOWN,    KC_UP,    KC_RIGHT,      KC_NO,        \
KC_NO,          KC_ALGR,    KC_NO,      KC_NO,      KC_NO,                              KC_INS,         KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,         \
                            KC_NO,      KC_NO,      KC_NO,                              KC_ENT,         KC_BSPC,    KC_DEL
    ),

    [_ACC] = LAYOUT_split_3x5_3_ex2( // MOUSE
TD(TD_BOOT),    KC_NO,      KC_NO,      KC_NO,      E_GRV,      KC_NO,          KC_NO,  U_RDO,          U_CIR,      U_GRV,      U_TRM,      U_UND,          \
A_GRV,          A_CIR,      KC_LCTL,    KC_LSFT,    E_TRM,      KC_NO,          KC_NO,  E_GRV,          E_AIG,      MS_DOWN,    I_CIR,      O_CIR,        \
KC_NO,          KC_ALGR,    KC_NO,      KC_NO,      E_CIR,                              E_CIR,          E_TRM,      MS_WHLD,    I_TRM,      O_TRM,        \
                            KC_NO,      KC_NO,      KC_NO,                              MS_BTN2,        MS_BTN1,    MS_BTN3
    ),

    [_MEDIA] = LAYOUT_split_3x5_3_ex2( // MEDIA
// pas de RGB ni de Bluetooth sur le Cornifi : touches RGB_* et OU_AUTO retirées
TD(TD_BOOT),    KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,          KC_NO,  KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,          \
KC_LGUI,        KC_LALT,    KC_LCTL,    KC_LSFT,    KC_NO,      KC_NO,          KC_NO,  KC_NO,          KC_MPRV,    KC_VOLD,    KC_VOLU,    KC_MNXT,        \
KC_NO,          KC_ALGR,    KC_NO,      KC_NO,      KC_NO,                              KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,          \
                            KC_NO,      KC_NO,      KC_NO,                              KC_MSTP,        KC_MPLY,    KC_MUTE
    ),

    [_NUM] = LAYOUT_split_3x5_3_ex2( // NUM
KC_LBRC,        KC_9,       KC_8,       KC_7,       KC_RBRC,    KC_NO,          KC_NO,  KC_NO,          KC_NO,      KC_NO,      KC_NO,      TD(TD_BOOT),    \
KC_SCLN,        KC_6,       KC_5,       KC_4,       KC_EQL,     KC_NO,          KC_NO,  KC_NO,          KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,        \
KC_GRV,         KC_3,       KC_2,       KC_1,       KC_BSLS,                            KC_NO,          KC_NO,      KC_NO,      KC_ALGR,    KC_NO,          \
                            KC_DOT,     KC_0,       KC_MINS,                            KC_NO,          KC_NO,      KC_NO
    ),

    [_SYM] = LAYOUT_split_3x5_3_ex2( // SYM
KC_LCBR,        KC_AMPR,    KC_ASTR,    KC_LPRN,    KC_RCBR,    KC_NO,          KC_NO,  KC_NO,          KC_NO,      KC_NO,      KC_NO,      TD(TD_BOOT),    \
KC_COLN,        KC_DLR,     KC_PERC,    KC_CIRC,    KC_PLUS,    KC_NO,          KC_NO,  KC_NO,          KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,        \
KC_TILD,        KC_EXLM,    KC_AT,      KC_HASH,    KC_PIPE,                            KC_NO,          KC_NO,      KC_NO,      KC_ALGR,    KC_NO,          \
                            KC_LPRN,    KC_RPRN,    KC_UNDS,                            KC_NO,          KC_NO,      KC_NO
    ),

    [_FUN] = LAYOUT_split_3x5_3_ex2( // FUN
KC_F12,         KC_F7,      KC_F8,      KC_F9,      KC_PSCR,    KC_NO,          KC_NO,  KC_NO,          KC_NO,      KC_NO,      KC_NO,      TD(TD_BOOT),    \
KC_F11,         KC_F4,      KC_F5,      KC_F6,      KC_SCRL,    KC_NO,          KC_NO,  KC_NO,          KC_LSFT,    KC_LCTL,    KC_LALT,    KC_LGUI,        \
KC_F10,         KC_F1,      KC_F2,      KC_F3,      KC_PAUS,                            KC_NO,          KC_NO,      KC_NO,      KC_ALGR,    KC_NO,          \
                            KC_APP,     KC_SPC,     KC_TAB,                             KC_NO,          KC_NO,      KC_NO
    ),
    // clang-format on
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // A
        case A_AIG:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("'") "a");
            }
            return false;
        case A_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("`") "a");
            }
            return false;
        case A_TRM:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("\"") "a");
            }
            return false;
        case A_CIR:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("6") "a");
            }
            return false;
        // E
        case E_AIG:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("'") "e");
            }
            return false;
        case E_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("`") "e");
            }
            return false;
        case E_TRM:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("\"") "e");
            }
            return false;
        case E_CIR:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("6") "e");
            }
            return false;
        // I
        case I_AIG:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("'") "i");
            }
            return false;
        case I_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("`") "i");
            }
            return false;
        case I_TRM:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("\"") "i");
            }
            return false;
        case I_CIR:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("6") "i");
            }
            return false;
        // O
        case O_AIG:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("'") "o");
            }
            return false;
        case O_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("`") "o");
            }
            return false;
        case O_TRM:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("\"") "o");
            }
            return false;
        case O_CIR:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("6") "o");
            }
            return false;
        // U
        case U_AIG:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("'") "u");
            }
            return false;
        case U_GRV:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("`") "u");
            }
            return false;
        case U_TRM:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("\"") "u");
            }
            return false;
        case U_CIR:
            if (record->event.pressed) {
                SEND_STRING(SS_ALGR("6") "u");
            }
            return false;
    }

    return true;
}

// Raw HID : couche active -> ordinateur (voir RAW_LAYER_MSG plus haut).
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
    uint8_t data[32] = {RAW_LAYER_MSG, get_highest_layer(state), get_mods()}; // 32 = RAW_EPSIZE (USB)
    raw_hid_send(data, sizeof(data));
}

layer_state_t layer_state_set_user(layer_state_t state) {
    send_state(state);
    return state;
}

// appelée en continu : envoie les changements de modificateurs (home row mods
// maintenus, touches Ctrl/Shift… des couches)
void housekeeping_task_user(void) {
    static uint8_t last_mods = 0;
    uint8_t        mods      = get_mods();
    if (mods != last_mods) {
        last_mods = mods;
        send_state(layer_state);
    }
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length > 0 && data[0] == RAW_LAYER_MSG) {
        raw_host_active = true;
        raw_host_seen   = timer_read32();
        send_state(layer_state);
    }
}
