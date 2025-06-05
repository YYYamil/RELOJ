/*********************************************************************************************************************
Copyright 2025, Yamil Tolaba <yamiltolaba@gmail.com>

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

/** @file main.c
 ** @brief Programa principal para controlar LEDs y teclas usando la capa de placa
 **/

/* === Headers files inclusions =============================================================== */

#include "bsp.h"
#include "digital.h"
#include <stdbool.h>

/* === Public function implementation ========================================================= */

int main(void) {
    // Inicializar la placa
    board_t board = BoardCreate();

    int divisor = 0;

    while (true) {
        // Control del LED azul (LED_B) con TEC_1
        if (DigitalInputGetIsActive(board->key_push)) { // Reemplaza Chip_GPIO_ReadPortBit == 0
                                                        // DigitalOutputActivate(led_blue); //
                                                        // Reemplazamos Chip_GPIO_SetPinState
            DigitalOutputActivate(board->led_blue);
        } else {
            DigitalOutputDeactivate(board->led_blue); // Reemplazamos Chip_GPIO_SetPinState
        }

        // Control del LED_1 con TEC_2
        if (DigitalInputWasActivated(board->key_toggle)) {
            DigitalOutputToggle(board->led_1); // Reemplazamos Chip_GPIO_SetPinToggle
        }

        // Control del LED_2 con TEC_3 y TEC_4
        if (DigitalInputGetIsActive(board->key_turn_on)) {
            DigitalOutputActivate(board->led_2); // Reemplazamos Chip_GPIO_SetPinState
        }
        if (DigitalInputGetIsActive(board->key_turn_off)) {
            DigitalOutputDeactivate(board->led_2); // Reemplazamos Chip_GPIO_SetPinState
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;

            DigitalOutputToggle(board->led_green); // Led Verde parpadeando
        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP"); // estoy ejecutando 25millones de veces una funcion que no hace nada
            }
        }
    }
    return 0;
}

/* === End of documentation ==================================================================== */