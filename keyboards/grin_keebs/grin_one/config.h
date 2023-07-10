// Copyright 2023 GRIN keebs (@policium)
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

#define MATRIX_MASKED

#define SOLENOID_PIN GP3
#define SOLENOID_PIN_ACTIVE_LOW
#define SOLENOID_MIN_DWELL 1
