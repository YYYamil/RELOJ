/*********************************************************************************************************************
Copyright (c) 2025, Tolaba Yamil <yamiltolaba@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file screen.h
 ** @brief Implentacion del modulo para la gestion de entrada y salidas digitales
 **/

/* === Headers files inclusions ==================================================================================== */

#include "screen.h"

#include <string.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

#ifndef SCREEN_MAX_DIGITS
#define SCREEN_MAX_DIGITS 8
#endif

/* === Private data type declarations ============================================================================== */

struct screen_s {
    uint8_t digits;
    uint8_t current_digit;
    uint8_t flashing_from;
    uint8_t flashing_to;
    uint8_t flashing_count;
    uint8_t flashing_frequency; 
    screen_driver_t driver;
    uint8_t value[SCREEN_MAX_DIGITS];
};
/* === Private function declarations =============================================================================== */


static const uint8_t IMAGES[] = {
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F, // 0
    SEGMENT_B | SEGMENT_C,                                                 // 1
    SEGMENT_A | SEGMENT_B | SEGMENT_D | SEGMENT_E | SEGMENT_G,             // 2
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_G,             // 3
    SEGMENT_B | SEGMENT_C | SEGMENT_F | SEGMENT_G,                         // 4
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G,             // 5
    SEGMENT_A | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, // 6
    SEGMENT_A | SEGMENT_B | SEGMENT_C,                                     // 7
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_E | SEGMENT_F | SEGMENT_G, // 8
    SEGMENT_A | SEGMENT_B | SEGMENT_C | SEGMENT_D | SEGMENT_F | SEGMENT_G  // 9
};

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */

screen_t ScreenCreate(uint8_t digits, screen_driver_t driver) {
    screen_t self = malloc(sizeof(struct screen_s));
    if (self) {
        if (digits > SCREEN_MAX_DIGITS) {
            digits = SCREEN_MAX_DIGITS;
        }
        self->digits = digits;
        self->driver = driver;
        self->current_digit = 0;
        self->flashing_count = 0;
        self->flashing_frequency = 0;
        self->flashing_from = 0;
        self->flashing_to = 0;
        memset(self->value, 0, SCREEN_MAX_DIGITS);
    }
    return self;
}
void ScreenWriteBCD(screen_t self, uint8_t value[], uint8_t size) {
    if (self && size > 0) {
        if (size > self->digits) {
            size = self->digits;
        }
        for (uint8_t i = 0; i < size; i++) {
            if (value[i] <= 9) {
                self->value[i] = IMAGES[value[i]];
            }
        }
    }
}
void ScreenRefresh(screen_t self) {
    if (self && self->driver) {
        self->driver->DigitsTurnOff();
        self->current_digit = (self->current_digit + 1) % self->digits;

        uint8_t segments = self->value[self->current_digit];

        if (self->flashing_frequency != 0) {
            if (self->current_digit >= self->flashing_from && self->current_digit <= self->flashing_to) {
                self->flashing_count = (self->flashing_count + 1) % self->flashing_frequency;
                if (self->flashing_count < (self->flashing_frequency / 2)) {
                    segments = 0;
                }
            }
        }

        self->driver->SegmentsUpdate(segments); // Usar 'segments'
        self->driver->DigitTurnOn(self->current_digit);
    }
}

int DisplayFlashDigits(screen_t self, uint8_t from, uint8_t to, uint16_t divisor) {
    if (!self || from > to || from >= SCREEN_MAX_DIGITS || to >= SCREEN_MAX_DIGITS) {
        return -1;
    }
    self->flashing_from = from;
    self->flashing_to = to;
    self->flashing_frequency = 2 * divisor; // Corregido
    self->flashing_count = 0;
    return 0;
}


/* === End of documentation ======================================================================================== */
