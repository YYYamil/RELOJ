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

#ifndef SCREEN_H_
#define SCREEN_H_

/** @file screen.h
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


#define SEGMENT_A (1 << 0)
#define SEGMENT_B (1 << 1)
#define SEGMENT_C (1 << 2)
#define SEGMENT_D (1 << 3)
#define SEGMENT_E (1 << 4)
#define SEGMENT_F (1 << 5)
#define SEGMENT_G (1 << 6)
#define SEGMENT_P (1 << 7)


/* === Public data type declarations =============================================================================== */


typedef struct screen_s * screen_t;

// typedef void(* digits_turn_off_t)(void);

// typedef void(* segments_update_t)(uint8_t);
// typedef void(* digit_turn_on_t)(uint8_t);

typedef struct screen_driver_s {
    void (*DigitsTurnOff)(void);
    void (*SegmentsUpdate)(uint8_t);
    void (*DigitTurnOn)(uint8_t);
} const * screen_driver_t;


// DigitsTurnOff(void);   
// SegmentTurnUpdate(uint8_t);
// DigitTurnOn(uint8_t);

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

/**
 * @brief Crea un objeto pantalla con el número de dígitos especificado.
 * @param digits Número de dígitos del display.
 * @param driver Puntero al controlador de hardware.
 * @return screen_t Puntero al objeto pantalla.
 */
screen_t ScreenCreate(uint8_t digits, screen_driver_t driver);

/**
 * @brief Escribe valores BCD en la pantalla.
 * @param screen Puntero al objeto pantalla.
 * @param value Arreglo de valores BCD.
 * @param size Tamaño del arreglo.
 */
void ScreenWriteBCD(screen_t screen, uint8_t value[], uint8_t size);
/**
 * @brief Refresca la pantalla mostrando el dígito actual.
 * @param screen Puntero al objeto pantalla.
 */
void ScreenRefresh(screen_t screen);

/**
 * @brief Función para hacer parpadear algunos dígitos de la pantalla
 *
 * @param display    Puntero al descriptor de la pantalla con la que se quiere operar
 * @param from       Posición del primer dígito que se quiere hacer parpadear
 * @param to         Posición del último dígito que se quiere hacer parpadear
 * @param frecuency  Factor de división de la frecuencia de refresco para el parpadeo
 */
int DisplayFlashDigits(screen_t screen, uint8_t from, uint8_t to, uint16_t divisor);

/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* SCREEN_H_ */
