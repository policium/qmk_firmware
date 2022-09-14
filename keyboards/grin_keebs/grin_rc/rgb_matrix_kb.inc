RGB_MATRIX_EFFECT(dj_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern float rgb_angle;
extern float speed;

static HSV dj_effect_math(HSV hsv, int16_t dx, int16_t dy, uint8_t time) {
    hsv.h = atan2_8(dy, dx) + rgb_angle / 360 * 255; /// * 360.0 * 3.1415;
    return hsv;
}

bool dj_effect(effect_params_t* params) {
    return effect_runner_dx_dy(params, &dj_effect_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
