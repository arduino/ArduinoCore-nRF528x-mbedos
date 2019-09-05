/* mbed Microcontroller Library
 * Copyright (c) 2017-2018 Nuvoton
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"
#include "partition_M2351.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NU_PININDEX_Pos                             0
#define NU_PININDEX_Msk                             (0xFFul << NU_PININDEX_Pos)
#define NU_PINPORT_Pos                              8
#define NU_PINPORT_Msk                              (0xFul << NU_PINPORT_Pos)
#define NU_PIN_MODINDEX_Pos                         12
#define NU_PIN_MODINDEX_Msk                         (0xFul << NU_PIN_MODINDEX_Pos)
#define NU_PIN_BIND_Pos                             16
#define NU_PIN_BIND_Msk                             (0x1ul << NU_PIN_BIND_Pos)

#define NU_PININDEX(PINNAME)                        (((unsigned int)(PINNAME) & NU_PININDEX_Msk) >> NU_PININDEX_Pos)
#define NU_PINPORT(PINNAME)                         (((unsigned int)(PINNAME) & NU_PINPORT_Msk) >> NU_PINPORT_Pos)
#define NU_PIN_BIND(PINNAME)                        (((unsigned int)(PINNAME) & NU_PIN_BIND_Msk) >> NU_PIN_BIND_Pos)
#define NU_PIN_MODINDEX(PINNAME)                    (((unsigned int)(PINNAME) & NU_PIN_MODINDEX_Msk) >> NU_PIN_MODINDEX_Pos)
#define NU_PINNAME(PORT, PIN)                       ((((unsigned int) (PORT)) << (NU_PINPORT_Pos)) | (((unsigned int) (PIN)) << NU_PININDEX_Pos))
#define NU_PINNAME_BIND(PINNAME, modname)           ((PinName) NU_PINNAME_BIND_(NU_PINPORT(PINNAME), NU_PININDEX(PINNAME), modname))
#define NU_PINNAME_BIND_(PORT, PIN, modname)        ((((unsigned int)(PORT)) << NU_PINPORT_Pos) | (((unsigned int)(PIN)) << NU_PININDEX_Pos) | (NU_MODINDEX(modname) << NU_PIN_MODINDEX_Pos) | NU_PIN_BIND_Msk)

/* Revise NU_PORT_BASE to be TrustZone-aware */
__STATIC_INLINE GPIO_T *NU_PORT_BASE(uint32_t PORT)
{
    uint32_t port_base = ((uint32_t) GPIOA_BASE) + 0x40 * PORT;
    
#if defined(SCU_INIT_IONSSET_VAL)
    if (SCU_INIT_IONSSET_VAL & (1 << (PORT + 0))) {
        port_base += NS_OFFSET;
    } 
#endif

    return ((GPIO_T *) port_base);
}

#define NU_MFP_POS(pin)                             ((pin % 8) * 4)
#define NU_MFP_MSK(pin)                             (0xful << NU_MFP_POS(pin))

/* TrustZone-aware version of GPIO_PIN_DATA to get GPIO pin data */
__STATIC_INLINE uint32_t NU_GET_GPIO_PIN_DATA(uint32_t PORT, uint32_t PIN)
{
#if defined(SCU_INIT_IONSSET_VAL)
    if (SCU_INIT_IONSSET_VAL & (1 << (PORT + 0))) {
        return GPIO_PIN_DATA_NS(PORT, PIN);
    } 
#endif
    
    return GPIO_PIN_DATA(PORT, PIN);
}

/* TrustZone-aware version of GPIO_PIN_DATA to set GPIO pin data */
__STATIC_INLINE void NU_SET_GPIO_PIN_DATA(uint32_t PORT, uint32_t PIN, uint32_t VALUE)
{
#if defined(SCU_INIT_IONSSET_VAL)
    if (SCU_INIT_IONSSET_VAL & (1 << (PORT + 0))) {
        GPIO_PIN_DATA_NS(PORT, PIN) = VALUE;
        return;
    }
#endif
    
    GPIO_PIN_DATA(PORT, PIN) = VALUE;
}

// LEGACY
#define NU_PINNAME_TO_PIN(PINNAME)                  NU_PININDEX(PINNAME)
#define NU_PINNAME_TO_PORT(PINNAME)                 NU_PINPORT(PINNAME)
#define NU_PINNAME_TO_MODSUBINDEX(PINNAME)          NU_PIN_MODINDEX(PINNAME)
#define NU_PORT_N_PIN_TO_PINNAME(PORT, PIN)         NU_PINNAME((PORT), (PIN))

typedef enum {
    PIN_INPUT,
    PIN_OUTPUT
} PinDirection;

typedef enum {
    /* Input pull mode */
    PullNone = 0,
    PullDown,
    PullUp,
    
    /* I/O mode */
    InputOnly,
    PushPullOutput,
    OpenDrain,
    QuasiBidirectional,
    
    /* Default input pull mode */
    PullDefault = PullUp
} PinMode;

typedef enum {
    // Not connected
    NC = (int)0xFFFFFFFF,
    
    // Generic naming
    PA_0    = NU_PORT_N_PIN_TO_PINNAME(0, 0), PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15,
    PB_0    = NU_PORT_N_PIN_TO_PINNAME(1, 0), PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, PB_11, PB_12, PB_13, PB_14, PB_15,
    PC_0    = NU_PORT_N_PIN_TO_PINNAME(2, 0), PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13,
    PD_0    = NU_PORT_N_PIN_TO_PINNAME(3, 0), PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7, PD_8, PD_9, PD_10, PD_11, PD_12, PD_13, PD_14,
    PE_0    = NU_PORT_N_PIN_TO_PINNAME(4, 0), PE_1, PE_2, PE_3, PE_4, PE_5, PE_6, PE_7, PE_8, PE_9, PE_10, PE_11, PE_12, PE_13, PE_14, PE_15,
    PF_0    = NU_PORT_N_PIN_TO_PINNAME(5, 0), PF_1, PF_2, PF_3, PF_4, PF_5, PF_6, PF_7, PF_8, PF_9, PF_10, PF_11,
    PG_0    = NU_PORT_N_PIN_TO_PINNAME(6, 0), PG_1, PG_2, PG_3, PG_4, PG_5, PG_6, PG_7, PG_8, PG_9, PG_10, PG_11, PG_12, PG_13, PG_14, PG_15,
    PH_0    = NU_PORT_N_PIN_TO_PINNAME(7, 0), PH_1, PH_2, PH_3, PH_4, PH_5, PH_6, PH_7, PH_8, PH_9, PH_10, PH_11,
   
    // Arduino UNO naming
    A0 = PB_11,
    A1 = PB_10,
    A2 = PB_9,
    A3 = PB_8,
    A4 = PB_4,
    A5 = PB_5,

    D0 = PA_8,
    D1 = PA_9,
    D2 = PB_7,
    D3 = PB_6,
    D4 = PB_3,
    D5 = PB_2,
    D6 = PC_12,
    D7 = PC_11,
    D8 = PC_9,
    D9 = PC_10,
    D10 = PF_9,
    D11 = PF_6,
    D12 = PF_7,
    D13 = PF_8,
    D14 = PG_3,
    D15 = PG_2,
    
    // Other board-specific naming
    
    // UART naming
    USBTX = PB_13,
    USBRX = PB_12,
    STDIO_UART_TX   = USBTX,
    STDIO_UART_RX   = USBRX,
    
    // I2C naming
    I2C_SCL = D15,
    I2C_SDA = D14,
    
    // LED naming
    LED1 = PA_10,
    LED2 = PA_11,
    LED3 = PA_10,  // No real LED. Just for passing ATS.
    LED4 = PA_11,  // No real LED. Just for passing ATS.
    LED_GREEN = LED1,
    
    // Button naming
    SW2 = PB_0,
    SW3 = PB_1,
    BUTTON1 = SW2,
    BUTTON2 = SW3,

    // Force PinName to 32-bit required by NU_PINNAME_BIND(...)
    FORCE_ENUM_PINNAME_32BIT = 0x7FFFFFFF,

} PinName;

#ifdef __cplusplus
}
#endif

#endif // MBED_PINNAMES_H
