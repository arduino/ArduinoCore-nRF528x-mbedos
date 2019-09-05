/***************************************************************************//**
* \file cyhal_hw_resources.h
*
* \brief
* Provides a struct definitions for configuration resources in the PDL.
*
********************************************************************************
* \copyright
* Copyright 2018-2019 Cypress Semiconductor Corporation
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
*******************************************************************************/

/**
* \addtogroup group_hal_hw_resources PSoC 6 Hardware Resources
* \ingroup group_hal_psoc6
* \{
* Struct definitions for configuration resources in the PDL.
*
* \defgroup group_hal_hw_resources_macros Macros
* \defgroup group_hal_hw_resources_functions Functions
* \defgroup group_hal_hw_resources_data_structures Data Structures
* \defgroup group_hal_hw_resources_enums Enumerated Types
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
* \addtogroup group_hal_hw_resources_enums
* \{
*/

/* NOTE: Any changes made to this enum must also be made to the hardware manager resource tracking */
/** Resource types that the hardware manager supports */
typedef enum
{
    CYHAL_RSC_ADC,       /*!< Analog to digital converter */
    CYHAL_RSC_BLESS,     /*!< Bluetooth communications block */
    CYHAL_RSC_CAN,       /*!< CAN communication block */
    CYHAL_RSC_CLKPATH,   /*!< System clock clock path, used to drive hfclks */
    CYHAL_RSC_CLOCK,     /*!< Clock divider */
    CYHAL_RSC_CRYPTO,    /*!< Crypto hardware accelerator */
    CYHAL_RSC_DAC,       /*!< Digital to analog converter */
    CYHAL_RSC_DMA,       /*!< DMA controller */
    CYHAL_RSC_GPIO,      /*!< General purpose I/O pin */
    CYHAL_RSC_I2S,       /*!< I2S communications block */
    CYHAL_RSC_LCD,       /*!< Segment LCD controller */
    CYHAL_RSC_LPCOMP,    /*!< Low power comparator */
    CYHAL_RSC_LPTIMER,   /*!< Low power timer */
    CYHAL_RSC_OPAMP,     /*!< Opamp */
    CYHAL_RSC_PDM,       /*!< PCM/PDM communications block */
    CYHAL_RSC_SMIF,      /*!< Quad-SPI communications block */
    CYHAL_RSC_RTC,       /*!< Real time clock */
    CYHAL_RSC_SCB,       /*!< Serial Communications Block */
    CYHAL_RSC_SDHC,      /*!< SD Host Controller */
    CYHAL_RSC_TCPWM,     /*!< Timer/Counter/PWM block */
    CYHAL_RSC_UDB,       /*!< UDB Array */
    CYHAL_RSC_USB,       /*!< USB communication block */
    CYHAL_RSC_INVALID,   /*!< Placeholder for invalid type */
} cyhal_resource_t;

/** \} group_hal_hw_resources_enums */


/**
* \addtogroup group_hal_hw_resources_data_structures
* \{
*/

/** Represents a particular instance of a resource on the chip */
typedef struct
{
    cyhal_resource_t type;      //!< The resource block type
    uint8_t          block_num; //!< The resource block index
    /**
      * The channel number, if the resource type defines multiple channels
      * per block instance. Otherwise, 0 */
    uint8_t          channel_num;
} cyhal_resource_inst_t;

/** \} group_hal_hw_resources_data_structures */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/** \} group_hal_hw_resources */
