/* Copyright (c) 2025, Tolaba Yamil <yamiltolaba@gmail.com>
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

/** \brief Implementación de la capa de placa para la EDU-CIAA-NXP
 **
 ** \addtogroup board Capa de placa
 ** \brief Capa de abstracción del hardware específico
 ** @{ */

/* === Headers files inclusions =============================================================== */

 #include "bsp.h"
 #include "chip.h"
 
 #include "poncho.h"
 #include "digital.h"
 #include "screen.h"
 #include <stdlib.h>
 
 /* === Private function declarations ========================================================== */
 
 static void DigitsTurnOff(void);
 static void SegmentsUpdate(uint8_t value);
 static void DigitTurnOn(uint8_t digit);
 
 /* === Private variable definitions =========================================================== */
 
 static const struct screen_driver_s screen_driver = {
     .DigitsTurnOff = DigitsTurnOff,
     .SegmentsUpdate = SegmentsUpdate,
     .DigitTurnOn = DigitTurnOn,
 };
 
 /* === Private function definitions =========================================================== */
 
 static void DigitsInit(void) {
     Chip_SCU_PinMuxSet(DIGIT_1_PORT, DIGIT_1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_1_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_1_GPIO, DIGIT_1_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_1_GPIO, DIGIT_1_BIT, true);
 
     Chip_SCU_PinMuxSet(DIGIT_2_PORT, DIGIT_2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_2_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_2_GPIO, DIGIT_2_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_2_GPIO, DIGIT_2_BIT, true);
 
     Chip_SCU_PinMuxSet(DIGIT_3_PORT, DIGIT_3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_3_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_3_GPIO, DIGIT_3_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_3_GPIO, DIGIT_3_BIT, true);
 
     Chip_SCU_PinMuxSet(DIGIT_4_PORT, DIGIT_4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | DIGIT_4_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, DIGIT_4_GPIO, DIGIT_4_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, DIGIT_4_GPIO, DIGIT_4_BIT, true);
 }
 
 static void SegmentsInit(void) {
     Chip_SCU_PinMuxSet(SEGMENT_A_PORT, SEGMENT_A_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_A_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_A_GPIO, SEGMENT_A_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_A_GPIO, SEGMENT_A_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_B_PORT, SEGMENT_B_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_B_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_B_GPIO, SEGMENT_B_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_B_GPIO, SEGMENT_B_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_C_PORT, SEGMENT_C_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_C_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_C_GPIO, SEGMENT_C_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_C_GPIO, SEGMENT_C_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_D_PORT, SEGMENT_D_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_D_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_D_GPIO, SEGMENT_D_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_D_GPIO, SEGMENT_D_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_E_PORT, SEGMENT_E_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_E_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_E_GPIO, SEGMENT_E_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_E_GPIO, SEGMENT_E_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_F_PORT, SEGMENT_F_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_F_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_F_GPIO, SEGMENT_F_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_F_GPIO, SEGMENT_F_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_G_PORT, SEGMENT_G_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_G_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_G_GPIO, SEGMENT_G_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_G_GPIO, SEGMENT_G_BIT, true);
 
     Chip_SCU_PinMuxSet(SEGMENT_P_PORT, SEGMENT_P_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | SEGMENT_P_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, true);
 }
 
 static void KeysInit(void) {
     Chip_SCU_PinMuxSet(KEY_F1_PORT, KEY_F1_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F1_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_F1_GPIO, KEY_F1_BIT, false);
 
     Chip_SCU_PinMuxSet(KEY_F2_PORT, KEY_F2_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F2_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_F2_GPIO, KEY_F2_BIT, false);
 
     Chip_SCU_PinMuxSet(KEY_F3_PORT, KEY_F3_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F3_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_F3_GPIO, KEY_F3_BIT, false);
 
     Chip_SCU_PinMuxSet(KEY_F4_PORT, KEY_F4_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_F4_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_F4_GPIO, KEY_F4_BIT, false);
 
     Chip_SCU_PinMuxSet(KEY_ACCEPT_PORT, KEY_ACCEPT_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_ACCEPT_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_ACCEPT_GPIO, KEY_ACCEPT_BIT, false);
 
     Chip_SCU_PinMuxSet(KEY_CANCEL_PORT, KEY_CANCEL_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_PULLUP | KEY_CANCEL_FUNC);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, KEY_CANCEL_GPIO, KEY_CANCEL_BIT, false);
 }
 
 static void BuzzerInit(void) {
     Chip_SCU_PinMuxSet(BUZZER_PORT, BUZZER_PIN, SCU_MODE_INBUFF_EN | SCU_MODE_INACT | BUZZER_FUNC);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, BUZZER_GPIO, BUZZER_BIT, false);
     Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, BUZZER_GPIO, BUZZER_BIT, true);
 }
 
 static void DigitsTurnOff(void) {
     Chip_GPIO_ClearValue(LPC_GPIO_PORT, DIGITS_GPIO, DIGITS_MASK);
     Chip_GPIO_ClearValue(LPC_GPIO_PORT, SEGMENTS_GPIO, SEGMENTS_MASK);
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, false);
 }
 
 static void SegmentsUpdate(uint8_t value) {
     Chip_GPIO_SetValue(LPC_GPIO_PORT, SEGMENTS_GPIO, (value & SEGMENTS_MASK));
     Chip_GPIO_SetPinState(LPC_GPIO_PORT, SEGMENT_P_GPIO, SEGMENT_P_BIT, (value & SEGMENT_P));
 }
 
 static void DigitTurnOn(uint8_t digit) {
     Chip_GPIO_SetValue(LPC_GPIO_PORT, DIGITS_GPIO, (1 << digit) & DIGITS_MASK);
 }
 
 /* === Public function implementations ========================================================= */
 
 board_t BoardCreate(void) {
     static struct board_s board = {0};
     static bool initialized = false;
 
     if (initialized) {
         return &board;
     }
 
     initialized = true;
 
     DigitsInit();
     SegmentsInit();
     KeysInit();
     BuzzerInit();
 
     board.screen = ScreenCreate(4, &screen_driver);
     board.buzzer = DigitalOutputCreate(BUZZER_GPIO, BUZZER_BIT);
     board.set_time = DigitalInputCreate(KEY_F1_GPIO, KEY_F1_BIT, true);
     board.set_alarm = DigitalInputCreate(KEY_F2_GPIO, KEY_F2_BIT, true);
     board.decrement = DigitalInputCreate(KEY_F3_GPIO, KEY_F3_BIT, true);
     board.increment = DigitalInputCreate(KEY_F4_GPIO, KEY_F4_BIT, true);
     board.accept = DigitalInputCreate(KEY_ACCEPT_GPIO, KEY_ACCEPT_BIT, true);
     board.cancel = DigitalInputCreate(KEY_CANCEL_GPIO, KEY_CANCEL_BIT, true);
 
     return &board;
 }
 
 /* === End of documentation ==================================================================== */
 
 /** @} End of module definition for doxygen */