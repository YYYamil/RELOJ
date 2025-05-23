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

/** @file digital.c
 ** @brief Codigo fuente del modulo para la gestion de entradas y salidas digitales
 **/

/* === Headers files inclusions ==================================================================================== */

#include "digital.h"
#include "config.h"
#include <chip.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* === Macros definitions ========================================================================================== */

/* === Private data type declarations ============================================================================== */

/*! Estructura que representa una salida digital */
struct digital_output_s {
    uint8_t port; /*<Puerto al que pertenece la salida*/
    uint8_t pin;  /*< Pin al que pertenece la salida*/
};
/*! Estructura que representa una entrada digital */
struct digital_input_s {
    uint8_t port; /*<Puerto al que pertenece la entrada*/
    uint8_t pin;  /*< Pin al que pertenece la entrada*/
    bool inverted;
    bool lastState;
};

/* === Private function declarations =============================================================================== */

/* === Private variable definitions ================================================================================ */

/* === Public variable definitions ================================================================================= */

/* === Private function definitions ================================================================================ */

/* === Public function implementation ============================================================================== */
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin) {
    digital_output_t self = malloc(sizeof(struct digital_output_s));
    if (self != NULL) {
        self->port = port;
        self->pin = pin;
        Chip_SCU_PinMuxSet(port, pin, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SCU_MODE_FUNC0);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, true);    // Configura como salida
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, port, pin, false); // Estado inicial apagado
    }
    return self;
}

void DigitalOutputActivate(digital_output_t self) {
    if (self != NULL) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, self->port, self->pin, true); // Activa el pin
    }
}
void DigitalOutputDeactivate(digital_output_t self) {
    if (self != NULL) {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, self->port, self->pin, false); // Desactiva el pin
    }
}
void DigitalOutputToggle(digital_output_t self) {
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, self->port, self->pin);
}

/*===================Configurando Entradas=============0*/
/**
 * @brief Funcion para crear una Entrada digital
 *
 */
digital_input_t DigitalInputCreate(uint8_t gpio, uint8_t bit, bool inverted) {
    digital_input_t self = malloc(sizeof(struct digital_input_s));
    if (self != NULL) {
        self->port = gpio;
        self->pin = bit;
        self->inverted = inverted;

        // Configuración SCU para la entrada (pull-up para teclas activas bajas)
        self->lastState = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, gpio, bit); // Inicializa con el estado real del pin
        if (self->inverted) {
            self->lastState = !self->lastState; // Aplica inversión si es necesario
        }
    }
    return self;
}

bool DigitalInputGetIsActive(digital_input_t self) {
    bool state = Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, self->port, self->pin); // llama a la funciona del fabricante
    if (self->inverted) {
        state = !state;
    }
    return state;
}

digital_states_t DigitalInputWasChanged(digital_input_t self) {
    if (self != NULL) {
        digital_states_t result = DIGITAL_INPUT_WAS_NO_CHANGE;

        bool state = DigitalInputGetIsActive(self);

        if (state && self->lastState) {
            result = DIGITAL_INPUT_WAS_ACTIVATED;

        } else if (!state && self->lastState) {
            result = DIGITAL_INPUT_WAS_DEACTIVATED;
        }
        self->lastState = state;
        return result;
    }
    return DIGITAL_INPUT_WAS_NO_CHANGE; // Valor por defecto si self es NULL
}

bool DigitalInputWasActivated(digital_input_t self) {
    return DIGITAL_INPUT_WAS_ACTIVATED == DigitalInputWasChanged(self);
}
bool DigitalInputWasDeactivated(digital_input_t self) {
    return DIGITAL_INPUT_WAS_DEACTIVATED == DigitalInputWasChanged(self);
}

/* === End of documentation ======================================================================================== */
