#include "grin_one.h"

const matrix_row_t matrix_mask[MATRIX_ROWS] = {
    0b111111110,
    0b111111101,
    0b111111011,
    0b111110111,
    0b111101111,
    0b111011111,
    0b110111111,
    0b101111111,
    0b011111111,
};

void keyboard_post_init_kb(void) {
    debug_enable = true;
    debug_matrix = true;
    debug_keyboard=true;
    //debug_mouse  = true;
    //setPinOutput(GP2);
    //writePinHigh(GP2);
    // Call the post init code.
    //rgblight_enable_noeeprom(); // enables Rgb, without saving settings
    //rgblight_sethsv_noeeprom(180, 255, 255); // sets the color to teal/cyan without saving
    //rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
}