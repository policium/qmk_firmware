/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#pragma once

/* ws2812 RGB LED */
#if defined(KEYBOARD_fractal)
#    define RGB_DI_PIN D2
#    undef RGBLED_NUM
#    define RGBLIGHT_ANIMATIONS
#    define RGBLED_NUM 29  // Number of LEDs
#    undef RGBLIGHT_HUE_STEP
#    define RGBLIGHT_HUE_STEP 8
#    undef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 8
#    undef RGBLIGHT_VAL_STEP
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 175
#    define RGBLIGHT_SLEEP

#    define RGBLIGHT_EFFECT_KNIGHT_OFFSET 3
#    define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 14
#    define AUDIO_PIN B7
#    define NO_MUSIC_MODE
#endif
