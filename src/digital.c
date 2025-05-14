/*********************************************************************************************************************
Copyright (c) Año, Nombre y Apellido del autor <correo@ejemplo.com>

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


struct digital input_s{
    uint8_t port;
    uint8_t pin;
    bool inverted;
    bool lastState;
}
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
    }
    return self;
}

void DigitalOutputActivate(digital_output_t self) {
}
void DigitalOutpuDeactivate(digital_output_t self) {
}
void DigitalOutputToggle(digital_output_t self) {
    Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, self->port, self->pin);
}


//Agrego entradas en teoria:

digital_input_t DigitalInputCreate(uint8_t gpio, uint8_bit, bool inverted){
    
}

bool digital_input_t DigitalInputGetIsActive(digital_input_t input){
        return true;

}

bool DigitalWasActivated(igital_input_t input){
    bool state = true; // llamar a la funcion del fabricante comparar on 1
    if (self->inverted){
        state = !state;
        
    }
    return state;
}
bool DigitalWasDeactivated(igital_input_t input){
    return DIGITAL_INPUT_WAS_ACTIVATE == DigitalWasChanged(self);
}

int DigitalWasChanged(igital_input_t input){
    digital_states_t result = DIGITAL_INPUT_NO_CHANGE;
    bool state= DigtialInputGetIsActivate(self);
    if (state!= self->lastState){
            result = DIGITAL_INPUT_WAS_ACTIVATED;

    } else if (!state && self->lastState){
        result = DIGITAL_INPUT_WAS_DEACTIVATED;
    }

    self->lastState =state;
    return result;
}

/* === End of documentation ======================================================================================== */
