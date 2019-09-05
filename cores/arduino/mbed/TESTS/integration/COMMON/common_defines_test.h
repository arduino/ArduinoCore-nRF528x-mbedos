/*
 * mbed Microcontroller Library
 * Copyright (c) 2006-2019 ARM Limited
 *
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
 */

#define ETHERNET 1
#define WIFI 2
#define MESH 3
#define CELLULAR 4

#if !defined(MBED_CONF_TARGET_NETWORK_DEFAULT_INTERFACE_TYPE)
#error [NOT_SUPPORTED] No network interface found on this target.
#endif

#if MBED_CONF_TARGET_NETWORK_DEFAULT_INTERFACE_TYPE == ETHERNET
#define TEST_NETWORK_TYPE "Ethernet"
#elif MBED_CONF_TARGET_NETWORK_DEFAULT_INTERFACE_TYPE == WIFI
#define TEST_NETWORK_TYPE "WiFi"
#elif MBED_CONF_TARGET_NETWORK_DEFAULT_INTERFACE_TYPE == MESH
#define TEST_NETWORK_TYPE "Mesh"
#elif MBED_CONF_TARGET_NETWORK_DEFAULT_INTERFACE_TYPE == CELLULAR
#define TEST_NETWORK_TYPE "Cellular"
#else
#error [NOT_SUPPORTED] Either WiFi, Ethernet or Cellular network interface need to be enabled
#endif

#define FS_FAT 1
#define FS_LFS 2

#if COMPONENT_SPIF
#define TEST_BLOCK_DEVICE_TYPE "SPIF"
#elif COMPONENT_QSPIF
#define TEST_BLOCK_DEVICE_TYPE "QSPIF"
#elif COMPONENT_DATAFLASH
#define TEST_BLOCK_DEVICE_TYPE "DATAFLASH"
#elif COMPONENT_SD
#define TEST_BLOCK_DEVICE_TYPE "SD"
#define TEST_USE_FILESYSTEM FS_FAT
#elif COMPONENT_FLASHIAP
#define TEST_BLOCK_DEVICE_TYPE "FLASHIAP"
#elif COMPONENT_SDIO
#define TEST_BLOCK_DEVICE_TYPE "SDIO"
#elif COMPONENT_NUSD
#define TEST_BLOCK_DEVICE_TYPE "NUSD"
#define TEST_USE_FILESYSTEM FS_FAT
#else
#define TEST_BLOCK_DEVICE_TYPE "UNKNOWN"
#endif

#if !defined(TEST_USE_FILESYSTEM)
#define TEST_USE_FILESYSTEM FS_LFS
#endif

#if TEST_USE_FILESYSTEM == FS_FAT
#define TEST_FILESYSTEM_TYPE "FAT"
#elif TEST_USE_FILESYSTEM == FS_LFS
#define TEST_FILESYSTEM_TYPE "LFS"
#else
#define TEST_FILESYSTEM_TYPE "UNKNOWN"
#endif

#define TEST_MEMORY_SIZE_10K 10240
#define TEST_MEMORY_SIZE_20K 20480
#define TEST_MEMORY_SIZE_40K 40960
#define TEST_MEMORY_SIZE_60K 61440
#define TEST_MEMORY_SIZE_80K 81920
#define TEST_MEMORY_SIZE_100K 102400
