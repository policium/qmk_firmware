// Copyright 2022 GRINkeebs (@policium)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "i2c_master.h"

extern i2c_status_t tca9555_status;
#undef I2C_TIMEOUT
#define I2C_TIMEOUT 1000

// I2C address:
// All address pins of the tca9555 are connected to the ground
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR (0b0100000 << 1)

// Register addresses
#define IODIRA 0x06  // i/o direction register
#define IODIRB 0x07
#define IREGP0 0x00  // GPIO pull-up resistor register
#define IREGP1 0x01
#define OREGP0 0x02  // general purpose i/o port register (write modifies OLAT)
#define OREGP1 0x03

bool         i2c_initialized = 0;
i2c_status_t tca9555_status = I2C_ADDR;

uint8_t init_tca9555(void) {
    print("starting init");
    tca9555_status = I2C_ADDR;

    // I2C subsystem
    if (i2c_initialized == 0) {
        i2c_init();
        i2c_initialized = true;
        wait_ms(I2C_TIMEOUT);
    }

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    uint8_t conf[2] = {
        // This means: read all pins of port 0
        0b11111111,
        // This means: read all pins of port 1
        0b11111111,
    };
    tca9555_status = i2c_writeReg(I2C_ADDR, IODIRA, conf, 2, I2C_TIMEOUT);

    return tca9555_status;
}

static uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;

static matrix_row_t read_cols(void);
static void unselect_row(uint8_t row);
static void unselect_rows(void);
static bool select_row(uint8_t row);

static uint8_t tca9555_reset_loop;

void matrix_init_custom(void) {
    tca9555_status = init_tca9555();

    unselect_rows();
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Select row and wait for row selecton to stabilize
    if (!select_row(current_row)) { // Select row
        return false;                     // skip NO_PIN row
    }
    // Skip the wait_us(30); as i2c is slow enough to debounce the io changes

    matrix_row_t temp = read_cols();

    // Unselect row
    unselect_row(current_row);

    if (current_matrix[current_row] != temp) {
        current_matrix[current_row] = temp;
        return true;
    }
    return false;
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    if (tca9555_status) {  // if there was an error
        if (++tca9555_reset_loop == 0) {
            // since tca9555_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
            // this will be approx bit more frequent than once per second
            dprint("trying to reset tca9555\n");
            tca9555_status = init_tca9555();
            if (tca9555_status) {
                dprint("tca9555 not responding\n");
            } else {
                dprint("tca9555 attached\n");
            }
        }
    }

    bool matrix_has_changed = false;

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_has_changed |= read_cols_on_row(current_matrix, current_row);
    }

    return matrix_has_changed;
}

static matrix_row_t read_cols(void) {
    if (tca9555_status) {  // if there was an error
        return 0;
    } else {
        matrix_row_t data = 0;
        uint8_t ports[2] = {0};
        tca9555_status = i2c_readReg(I2C_ADDR, IREGP0, ports, 2, I2C_TIMEOUT);
        if (tca9555_status) {  // if there was an error
            // do nothing
            return 0;
        } else {
            uint8_t port0 = ports[0];
            uint8_t port1 = ports[1];

            data =
                (port1&(1<<4) ? 0 : (MATRIX_ROW_SHIFTER<<0)) |
                (port1&(1<<5) ? 0 : (MATRIX_ROW_SHIFTER<<1)) |
                (port1&(1<<6) ? 0 : (MATRIX_ROW_SHIFTER<<2)) |
                (port1&(1<<7) ? 0 : (MATRIX_ROW_SHIFTER<<3)) |
                (port1&(1<<2) ? 0 : (MATRIX_ROW_SHIFTER<<4)) |
                (port1&(1<<1) ? 0 : (MATRIX_ROW_SHIFTER<<5)) |
                (port1&(1<<0) ? 0 : (MATRIX_ROW_SHIFTER<<6)) |
                (port0&(1<<6) ? 0 : (MATRIX_ROW_SHIFTER<<7)) |
                (port0&(1<<5) ? 0 : (MATRIX_ROW_SHIFTER<<8)) |
                (port0&(1<<7) ? 0 : (MATRIX_ROW_SHIFTER<<9)) |
                (port1&(1<<3) ? 0 : (MATRIX_ROW_SHIFTER<<10)) |
                (port0&(1<<1) ? 0 : (MATRIX_ROW_SHIFTER<<11)) |
                (port0&(1<<2) ? 0 : (MATRIX_ROW_SHIFTER<<12)) |
                (port0&(1<<3) ? 0 : (MATRIX_ROW_SHIFTER<<13)) |
                (port0&(1<<0) ? 0 : (MATRIX_ROW_SHIFTER<<14)) |
                (port0&(1<<4) ? 0 : (MATRIX_ROW_SHIFTER<<15));

            tca9555_status = I2C_STATUS_SUCCESS;
            return data;
        }
    }
}

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput(pin);
        writePinLow(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput(pin);
        writePinHigh(pin);
#else
        setPinInputHigh(pin);
#endif
    }
}

static void unselect_rows(void) {
    for (uint x = 0; x < MATRIX_ROWS; x++) {
        unselect_row(x);
    }
}
