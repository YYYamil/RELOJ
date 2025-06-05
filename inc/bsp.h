#ifndef BSP_H_
#define BSP_H_

/** @file bsp.h
 ** @brief Declaraciones para la capa de placa específica
 **/

/* === Headers files inclusions ==================================================================================== */

#include "digital.h"
#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public data type declarations =============================================================================== */

/**
 * @brief Estructura que representa el objeto de la placa
 */
typedef struct board_s * board_t;

/**
 * @brief Estructura interna que representa la placa
 */
struct board_s {
    digital_output_t led_green;
    digital_output_t led_blue;
    digital_output_t led_1;
    digital_output_t led_2;
    // Crear instancias de entradas digitales (teclas activas bajas)
    digital_input_t key_push;
    digital_input_t key_toggle;
    digital_input_t key_turn_on;
    digital_input_t key_turn_off;
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