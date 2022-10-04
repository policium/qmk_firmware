// Copyright 2022 GRINkeebs (@policium)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

//#define RP2040_FLASH_GD25Q64CS
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP18
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define WS2812_PIO_USE_PIO1

#define DRIVER_LED_TOTAL 64

#define CIRQUE_PINNACLE_TAP_ENABLE
