/* Copyright (c) 2025, Tolaba Yamil <yamiltolaba@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Simple sample of use LPC HAL gpio functions
 **
 ** \addtogroup samples Sample projects
 ** \brief Sample projects to use as a starting point
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "chip.h"
#include <stdbool.h>

#include "board.h"
#include "cia.h"
#include "digital.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void) {

    // Inicializar la placa
    BoardInitialize();

    digital_output_t led_green = DigitalOutputCreate(LED_3_GPIO, LED_3_BIT);
    digital_output_t led_blue = DigitalOutputCreate(LED_B_GPIO, LED_B_BIT);
    digital_output_t led_1 = DigitalOutputCreate(LED_1_GPIO, LED_1_BIT);
    digital_output_t led_2 = DigitalOutputCreate(LED_2_GPIO, LED_2_BIT);

    int divisor = 0;
    // bool current_state, last_state = false;

    // Crear instancias de entradas digitales (teclas activas bajas)
    digital_input_t key_push = DigitalInputCreate(TEC_1_GPIO, TEC_1_BIT, true);
    digital_input_t key_toggle = DigitalInputCreate(TEC_2_GPIO, TEC_2_BIT, true);
    digital_input_t key_turn_on = DigitalInputCreate(TEC_3_GPIO, TEC_3_BIT, true);
    digital_input_t key_turn_off = DigitalInputCreate(TEC_4_GPIO, TEC_4_BIT, true);

    /**********Canales RGB**************/
    Chip_SCU_PinMuxSet(LED_R_PORT, LED_R_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_R_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_R_GPIO, LED_R_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, LED_R_GPIO, LED_R_BIT, true);

    Chip_SCU_PinMuxSet(LED_G_PORT, LED_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_G_FUNC);
    Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED_G_GPIO, LED_G_BIT, false);
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, LED_G_GPIO, LED_G_BIT, true);

    Chip_SCU_PinMuxSet(LED_B_PORT, LED_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_B_FUNC);

    /******************/
    Chip_SCU_PinMuxSet(LED_1_PORT, LED_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_1_FUNC);

    Chip_SCU_PinMuxSet(LED_2_PORT, LED_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_2_FUNC);

    Chip_SCU_PinMuxSet(LED_3_PORT, LED_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | LED_3_FUNC);

    /******************/
    Chip_SCU_PinMuxSet(TEC_1_PORT, TEC_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_1_FUNC);

    Chip_SCU_PinMuxSet(TEC_2_PORT, TEC_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_2_FUNC);

    Chip_SCU_PinMuxSet(TEC_3_PORT, TEC_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_3_FUNC);

    Chip_SCU_PinMuxSet(TEC_4_PORT, TEC_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | TEC_4_FUNC);

    while (true) {
        // Control del LED azul (LED_B) con TEC_1
        if (DigitalInputGetIsActive(
                key_push)) { // Reemplaza Chip_GPIO_ReadPortBit == 0            DigitalOutputActivate(led_blue); //
                             // Reemplazamos Chip_GPIO_SetPinState
            DigitalOutputActivate(led_blue);
        } else {
            DigitalOutputDeactivate(led_blue); // Reemplazamos Chip_GPIO_SetPinState
        }

        // Control del LED_1 con TEC_2
        if (DigitalInputWasActivated(key_toggle)) {
            DigitalOutputToggle(led_1); // Reemplazamos Chip_GPIO_SetPinToggle
        }

        // Control del LED_2 con TEC_3 y TEC_4
        if (DigitalInputGetIsActive(key_turn_on)) {
            DigitalOutputActivate(led_2); // Reemplazamos Chip_GPIO_SetPinState
        }
        if (DigitalInputGetIsActive(key_turn_off)) {
            DigitalOutputDeactivate(led_2); // Reemplazamos Chip_GPIO_SetPinState
        }

        divisor++;
        if (divisor == 5) {
            divisor = 0;

            DigitalOutputToggle(led_green); // Led Verde parpadeando
        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP"); // estoy ejecutando 25millones de veces una funcion que no hace nada
            }
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
