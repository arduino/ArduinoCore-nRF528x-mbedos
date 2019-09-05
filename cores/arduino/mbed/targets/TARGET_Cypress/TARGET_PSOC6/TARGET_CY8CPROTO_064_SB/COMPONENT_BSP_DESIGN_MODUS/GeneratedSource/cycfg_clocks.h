/*******************************************************************************
* File Name: cycfg_clocks.h
*
* Description:
* Clock configuration
* This file was automatically generated and should not be modified.
* 
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
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
********************************************************************************/

#if !defined(CYCFG_CLOCKS_H)
#define CYCFG_CLOCKS_H

#include "cycfg_notices.h"
#include "cy_sysclk.h"

#if defined(__cplusplus)
extern "C" {
#endif

#define peri_0_div_16_0_ENABLED 1U
#define peri_0_div_16_0_HW CY_SYSCLK_DIV_16_BIT
#define peri_0_div_16_0_NUM 0U
#define CYBSP_DEBUG_UART_CLK_DIV_ENABLED 1U
#define CYBSP_DEBUG_UART_CLK_DIV_HW CY_SYSCLK_DIV_8_BIT
#define CYBSP_DEBUG_UART_CLK_DIV_NUM 0U
#define CYBSP_I2C_CLK_DIV_ENABLED 1U
#define CYBSP_I2C_CLK_DIV_HW CY_SYSCLK_DIV_8_BIT
#define CYBSP_I2C_CLK_DIV_NUM 1U

void init_cycfg_clocks(void);

#if defined(__cplusplus)
}
#endif


#endif /* CYCFG_CLOCKS_H */
