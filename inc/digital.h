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

#ifndef DIGITAL_H_
#define DIGITAL_H_

/** @file digital.h
 ** @brief Declaraciones del modulo para la gestion de entrada y salidas digitales
 **/

/* === Headers files inclusions ==================================================================================== */

#include <stdbool.h>
#include <stdint.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

//! Estructura que representa una salida digital
typedef struct digital_output_s * digital_output_t;

//! Estructura que representa una Entrada digital
typedef struct digital_input_s * digital_input_t;
//! Estructura que representa los estados posibles
typedef enum digital_states_e {
    DIGITAL_INPUT_WAS_DEACTIVATED = -1,
    DIGITAL_INPUT_WAS_NO_CHANGE = 0,
    DIGITAL_INPUT_WAS_ACTIVATED = 1,
} digital_states_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/*===================Configurando Salidas=============0*/

/**
 * @brief Funcion para crear una salida .-NombredeclaseMetodo - nos quedamos 2 para funcionar con un puerto y un pin
 *
 * @param port  Puerto que se utiliza
 * @param pin   Bit utilizado
 * @return digital_output_t Puntero a una salida digital

 */
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);

/**
 * @brief Funcion de activacion del pin (le digo al pin para que se active)
 *
 * @param self
 */
void DigitalOutputActivate(digital_output_t self);

/**
 * @brief Funcion para desactivar un pin
 *
 * @param self
 */
void DigitalOutputDeactivate(digital_output_t self);

/**
 * @brief Funcion para cambiar estado de un pin
 *
 * @param self
 */
void DigitalOutputToggle(digital_output_t self);

/*===================Configurando Entradas=============0*/
/**
 * @brief Funcion para crear una Entrada digital
 *
 * @param gpio  Puerto gpio utilizado
 * @param bit   Bit utilizado
 * @param inverted Puntero a una instancia de entrada
 */
digital_input_t DigitalInputCreate(uint8_t gpio, uint8_t bit, bool inverted);

/**
 * @brief   Funcion para si una entrada cambio de estado
 *
 * @param input     Variable puntero
 * @return true     En caso afirmativo
 * @return false    En caso negativo
 */

bool DigitalInputGetIsActive(digital_input_t input);
/**
 * @brief Funcion para Activar una entrada
 *
 * @param input Puntero a una instancia de entrada
 * @return true
 * @return false
 */
bool DigitalInputWasActivated(digital_input_t input);
/**
 * @brief Funcion para desactivar una entrada
 *
 * @param self Puntero a una instancia de entrada
 * @return true
 * @return false
 */
bool DigitalInputWasDeactivated(digital_input_t self);

/**
 * @brief Funcion para representar los distintos estados
 *
 * @param input     Puntero a una instancia de entrada
 * @return  enum digital_states_e
 */

enum digital_states_e DigitalInputWasChanged(digital_input_t input);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* DIGITAL_H_ */
