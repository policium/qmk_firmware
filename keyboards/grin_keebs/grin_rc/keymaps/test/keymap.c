#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_INS,  KC_HOME, KC_SPC,  KC_DEL,  KC_END,  KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    )
};

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0,  1,  2,  3,  4,  5,  6 },
    { 27, 26, 25, 24, 23, 22, 21 },
    { 28, 29, 30, 31, 32, 33, 34 },
    { 52, 51, 50, 49, 48, 47, 46 },
    { 53, 54, 55, 56, 57, 58, 59 },
    { 13, 12, 11, 10, 9,  8,  7 },
    { 14, 15, 16, 17, 18, 19, 20 },
    { NO_LED, 40, 39, 38, 37, 36, 35 },
    { NO_LED, NO_LED, 41, 42, 43, 44, 45 },
    { 66, 65, 64, 63, 62, 61, 60 }
}, {
    // LED Index to Physical Positon
    { 0,   0 },  { 17,  0 },  { 35,  1 },  { 52,  5 },  { 68,  10 }, { 86,  14 }, { 103, 15 }, { 121, 14 }, { 138, 10 }, { 155, 5 },  { 172, 1 },  { 190, 0 },  { 207, 0 },  { 224, 0 },
    { 228, 17 }, { 211, 17 }, { 194, 17 }, { 176, 17 }, { 159, 20 }, { 142, 25 }, { 125, 30 }, { 108, 32 }, { 90,  31 }, { 73,  28 }, { 56,  23 }, { 39,  18 }, { 22,  17 }, { 0,   17 },
    { 0,   33 }, { 26,  33 }, { 43,  36 }, { 60,  41 }, { 77,  45 }, { 95,  48 }, { 112, 48 }, { 130, 45 }, { 146, 41 }, { 163, 36 }, { 181, 33 }, { 198, 33 }, { 224, 33 },
    { 207, 50 }, { 185, 50 }, { 168, 51 }, { 150, 56 }, { 134, 61 }, { 117, 64 }, { 99,  65 }, { 82,  63 }, { 64,  59 }, { 48,  54 }, { 30,  50 }, { 4,   50 },
    { 0,   66 }, { 17,  66 }, { 35,  67 }, { 52,  71 }, { 69,  76 }, { 90,  81 }, { 117, 81 }, { 138, 76 }, { 155, 71 }, { 172, 67 }, { 190, 66 }, { 207, 66 }, { 224, 66 }
}, {
    // LED Index to Flag
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

#define TP_L1 A13
#define TP_L2 A10
#define TP_L3 A9
#define TP_L4 A8
#define TP_R1 C14
#define TP_R2 C13
#define TP_R3 C15
#define TP_R4 A2
#define TP_1 A1

static bool l1_tapped = false;
static bool l2_tapped = false;
static bool l3_tapped = false;
static bool l4_tapped = false;
static bool r1_tapped = false;
static bool r2_tapped = false;
static bool r3_tapped = false;
static bool r4_tapped = false;
static bool t1_tapped = false;

static void read_left_value(void) {
    l1_tapped = !readPin(TP_L1);
    l2_tapped = !readPin(TP_L2);
    l3_tapped = !readPin(TP_L3);
    l4_tapped = !readPin(TP_L4);
}

static void read_right_value(void) {
    r1_tapped = !readPin(TP_R1);
    r2_tapped = !readPin(TP_R2);
    r3_tapped = !readPin(TP_R3);
    r4_tapped = !readPin(TP_R4);
}

static void read_tap_value(void) {
    t1_tapped = !readPin(TP_1);
}

void Keyboard_pre_init_user(void) {
    setPinInputHigh(TP_L1);
    setPinInputHigh(TP_L2);
    setPinInputHigh(TP_L3);
    setPinInputHigh(TP_L4);
    setPinInputHigh(TP_R1);
    setPinInputHigh(TP_R2);
    setPinInputHigh(TP_R3);
    setPinInputHigh(TP_R4);
    setPinInputHigh(TP_1);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
}

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    read_left_value();
    read_right_value();
    read_tap_value();

    // テスト点滅
    bool blink = (timer_read() % 1000) < 500;
    oled_write_P(blink ? PSTR("test") : PSTR("    "), false);

    // Left
    oled_set_cursor(0, 1);
    oled_write_P(l1_tapped ? PSTR("L1") : PSTR("  "), false);
    oled_set_cursor(3, 1);
    oled_write_P(l2_tapped ? PSTR("L2") : PSTR("  "), false);
    oled_set_cursor(6, 1);
    oled_write_P(l3_tapped ? PSTR("L3") : PSTR("  "), false);
    oled_set_cursor(9, 1);
    oled_write_P(l4_tapped ? PSTR("L4") : PSTR("  "), false);

    // Right
    oled_set_cursor(0, 2);
    oled_write_P(r1_tapped ? PSTR("R1") : PSTR("  "), false);
    oled_set_cursor(3, 2);
    oled_write_P(r2_tapped ? PSTR("R2") : PSTR("  "), false);
    oled_set_cursor(6, 2);
    oled_write_P(r3_tapped ? PSTR("R3") : PSTR("  "), false);
    oled_set_cursor(9, 2);
    oled_write_P(r4_tapped ? PSTR("R4") : PSTR("  "), false);

    // Tap
    oled_set_cursor(0, 3);
    oled_write_P(t1_tapped ? PSTR("TAP") : PSTR("   "), false);

    return false;
}
#endif
