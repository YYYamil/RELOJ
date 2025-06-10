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
#include <stdbool.h>

/* === Public function implementation ========================================================= */

int main(void) {
    uint8_t value[4] = {1, 2, 3, 4};
    board_t board = BoardCreate();

    ScreenWriteBCD(board->screen, value, 4);
    DisplayFlashDigits(board->screen, 2, 3, 50); // Corregido

    while (true) {
        // Refrescar el display
        ScreenRefresh(board->screen);

        // Ejemplo: Activar zumbador con KEY_F1
        if (DigitalInputGetIsActive(board->set_time)) {
            DigitalOutputActivate(board->buzzer);
        } else {
            DigitalOutputDeactivate(board->buzzer);
        }

        // Ejemplo: Incrementar valor con KEY_F4
        if (DigitalInputWasActivated(board->increment)) {
            value[0] = (value[0] + 1) % 10;
            ScreenWriteBCD(board->screen, value, 4);
        }

        // Retardo simple (mejorar con temporizador en el futuro)
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 2500; j++) {
                __asm("NOP");
            }
        }
    }
    return 0;
}
/* === End of documentation ==================================================================== */