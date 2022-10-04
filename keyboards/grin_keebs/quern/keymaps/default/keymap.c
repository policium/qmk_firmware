#include QMK_KEYBOARD_H

enum layer_names {
  _DEFAULT,
  _LOWER,
  _RAISE,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,                      KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,             KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
                          KC_LALT, LT(_LOWER,KC_LANG2),       KC_SPC,  KC_BTN1, KC_BTN2, KC_SPC,  LT(_RAISE,KC_LANG1),       MO(3)
    ),
    [_LOWER] = LAYOUT(
        KC_GRV,  _______, _______, _______, _______, _______, _______,                   _______, _______, KC_LBRC, KC_RBRC, _______, _______, KC_DEL,
        _______, _______, _______, _______, _______, _______,                            _______, _______, KC_UP,   _______, _______,          _______,
        _______, _______, _______, _______, _______, _______,                            _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT,          _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, KC_BSLS,          _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, _______, _______, _______, _______, _______,                            _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,          _______,
        _______, _______, _______, _______, _______, _______,                            _______, KC_INS,  KC_HOME, KC_PGUP, KC_BSPC,          _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, KC_DEL,  KC_END,  KC_PGDN,          _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [_ADJUST] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,                            _______, _______, KC_PSCR, KC_SCRL, KC_PAUS,          _______,
        _______, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,                            _______, KC_INS,  KC_HOME, KC_PGUP, KC_BSPC,          _______,
        _______, _______, _______, _______, _______, _______,                            _______, _______, KC_DEL,  KC_END,  KC_PGDN,          _______,
                                            _______, _______, _______, _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_DEFAULT] = { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN) },
    [_LOWER] = { ENCODER_CCW_CW(KC_LEFT, KC_RIGHT) },
    [_RAISE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
};
#endif

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_enable=true;
  //debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

#ifdef OLED_ENABLE
uint16_t startup_timer = 0;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,  0};
    oled_write_P(qmk_logo, false);
}

/*void render_layer_state(void){
    oled_write_P(PSTR("Layer:"), false);

    switch(get_highest_layer(layer_state)){
        case _DEFAULT:
            oled_write_P(PSTR(" Default\n"), false);
            break;

        case _LOWER:
            oled_write_P(PSTR(" Lower \n"), true);
            break;

        case _RAISE:
            oled_write_P(PSTR(" Raise\n"), true);
            break;

        case _ADJUST:
            oled_write_P(PSTR(" Adjust\n"), true);
            break;

        default:
            break;
    }
}*/
static void render_layer(void) {
    led_t led_state = host_keyboard_led_state();
    // clang-format off
    static const char PROGMEM logo[][3][7] = {
        {{0x97, 0x98, 0x99, 0x9A, 0}, {0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0}, {0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0}}, /* l      num      CB */
        {{0xB7, 0xB8, 0xB9, 0xBA, 0}, {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0}, {0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0}}, /* 1      num      CB */
        {{0xD7, 0xD8, 0xD9, 0xDA, 0}, {0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0}, {0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0}}, /* 1      cap      CB */
        {{0xF7, 0xF8, 0xF9, 0xFA, 0}, {0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0}, {0xFB, 0xFC, 0xFD, 0xFE, 0xFF, 0}}, /* l      cap      CB */
        {{0xB7, 0xC0, 0xC1, 0xBA, 0}, {0xB7, 0xC2, 0xC3, 0xBA, 0},             {0xB7, 0xC4, 0xC5, 0xBA, 0}},       /* 2       3       4  */
        {{0xD7, 0xE0, 0xE1, 0xDA, 0}, {0xD7, 0xE2, 0xE3, 0xDA, 0},             {0xD7, 0xE4, 0xE5, 0xDA, 0}},       /* 2       3       4  */
    };
    // clang-format on
    oled_set_cursor(0, 0);
    oled_write_P(logo[0][0], false);
    oled_set_cursor(0, 3);
    oled_write_P(logo[3][0], false);
    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_set_cursor(0, 1);
            oled_write_P(logo[1][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[2][0], false);
            break;
        case _LOWER:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][0], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][0], false);
            break;
        case _RAISE:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][1], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][1], false);
            break;
        case _ADJUST:
            oled_set_cursor(0, 1);
            oled_write_P(logo[4][2], false);
            oled_set_cursor(0, 2);
            oled_write_P(logo[5][2], false);
            break;
        default:
            oled_set_cursor(0, 1);
            oled_write_P(PSTR("    "), false);
            oled_set_cursor(0, 2);
            oled_write_P(PSTR("    "), false);
    }
    oled_set_cursor(8, 0);
    oled_write_P(led_state.num_lock ? logo[0][1] : PSTR("      "), false);
    oled_set_cursor(8, 1);
    oled_write_P(led_state.num_lock ? logo[1][1] : PSTR("      "), false);
    oled_set_cursor(8, 2);
    oled_write_P(led_state.caps_lock ? logo[2][1] : PSTR("      "), false);
    oled_set_cursor(8, 3);
    oled_write_P(led_state.caps_lock ? logo[3][1] : PSTR("      "), false);

    oled_set_cursor(16, 0);
    oled_write_P(logo[0][2], false);
    oled_set_cursor(16, 1);
    oled_write_P(logo[1][2], false);
    oled_set_cursor(16, 2);
    oled_write_P(logo[2][2], false);
    oled_set_cursor(16, 3);
    oled_write_P(logo[3][2], false);
}

// static void render_leds(void)
// {
//     // Host Keyboard LED Status
//     led_t led_state = host_keyboard_led_state();
//     oled_write_P(led_state.num_lock ? PSTR("NUMLK")     : PSTR("     "), false);
//     oled_write_P(led_state.caps_lock ? PSTR("CAPLK")    : PSTR("     "), false);
//     oled_write_P(led_state.scroll_lock ? PSTR("SCRLK")  : PSTR("     "), false);
//     oled_write_P(PSTR("\n"), false);
// }

void render_mode(void) {
    switch (layer_state) {
        case _DEFAULT:
            oled_write_P(PSTR("scroll\n"), false);
            break;

        case _LOWER:
            oled_write_P(PSTR("volume control\n"), false);
            break;

        case _RAISE:
            oled_write_P(PSTR("cursor control\n"), false);
            break;

        case _ADJUST:
            oled_write_P(PSTR("rgb VAL control\n"), false);
            break;

        default:
            break;
    }
}

bool oled_task_user(void) {
    static bool finished_timer = false;
    if (!finished_timer && (timer_elapsed(startup_timer) < 3000)) {
        render_logo();
    } else {
        if (!finished_timer) {
            oled_clear();
            finished_timer = true;
        }
        render_layer();
        //render_mode();
    }
    return false;
}
#endif
