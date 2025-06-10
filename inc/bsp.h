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
#ifndef BSP_H_
#define BSP_H_

/** @file bsp.h
 ** @brief Configuraciones para soporte de placa de hardware
 **/


/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif
/* === Public macros definitions ==================================================================================== */

#include "digital.h"
#include "screen.h"

#include <stdbool.h>
#include <stdint.h>


/* === Public data type declarations =============================================================================== */

/**
 * @brief Estructura que representa el objeto de la placa
 */
typedef struct board_s * board_t;

/**
 * @brief Estructura interna que representa la placa
 */
struct board_s {
    digital_output_t buzzer;
    digital_input_t set_time;
    digital_input_t set_alarm;
    digital_input_t decrement;
    digital_input_t increment;
    digital_input_t accept;
    digital_input_t cancel;
    screen_t screen;

};

/* === Public function declarations ================================================================================ */

/**
 * @brief Crea un objeto que representa la placa con sus recursos configurados
 *
 * @return board_t Puntero al objeto de la placa
 */
board_t BoardCreate(void);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* BSP_H_ */