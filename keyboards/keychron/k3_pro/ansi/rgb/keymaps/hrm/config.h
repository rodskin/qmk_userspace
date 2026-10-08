// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Home row mods : mêmes réglages que le Cornifi (mimi_qwerty).
// Tap puis maintien rapide = modificateur (pas d'auto-repeat de la lettre).
#define QUICK_TAP_TERM 0

// Caps Lock devenu Échap/Ctrl : les deux Shift ensemble activent Caps Word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Délai par touche (get_tapping_term dans keymap.c) : Caps Lock à 100 ms
// comme kanata, home row mods au défaut de 200 ms
#define TAPPING_TERM_PER_KEY

// LEDs : blanc uni par défaut (saturation 0). Ne s'applique qu'à la
// réinitialisation de l'EEPROM (reset usine Fn + J + Z, 3 s) : sinon le
// réglage sauvegardé (Fn + Q/A/F…) reste prioritaire
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_SAT 0
