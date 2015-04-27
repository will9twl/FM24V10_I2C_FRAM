/*
  FM24VN10.h
  ==========
  William Tan, Feb 2015
*/

#ifndef _FM24VN10_H
#define _FM24VN10_H

#include "stm32f4xx_hal.h"

/*
Memory Slave Device Address
===============================================================================
  MSB                           LSB
Bits 7 6 5 4 |   3  2   |  1   |  0       
     1 0 1 0    A2 A1     A16    R/W#
    Slave ID    Device    Page
                Select   Select
===============================================================================
*/
#define FRAM_SLAVE_DEV0_ADDR    0xA0
#define FRAM_SLAVE_DEV1_ADDR    0xA4
#define FRAM_SLAVE_DEV2_ADDR    0xA8
#define FRAM_SLAVE_DEV3_ADDR    0xAC

#define FRAM_PAGE_SELECT_H      0x02 //10000h to 1FFFFh (17-bit memory address) - P/S bit set to High (MSB)
#define FRAM_PAGE_SELECT_L      0x00 //00000h to 0FFFFh (17-bit memory address) - P/s bit set to Low (MSB)
#define FRAM_WRITE_TO_SLAVE     0x00
#define FRAM_READ_FROM_SLAVE    0x01

uint32_t FRAM_MultiByte_Write(I2C_HandleTypeDef *hi2c, uint32_t mem_addr, uint8_t *pData, uint16_t size);
uint32_t FRAM_MultiByte_Selective_Read(I2C_HandleTypeDef *hi2c, uint32_t mem_addr, uint8_t *pData, uint16_t size);

//Sleep current: 8uA (max), Standby current: 150uA (max), Average current: 250uA (at 400kHz)
uint32_t FRAM_Enter_Sleep_Mode(I2C_HandleTypeDef *hi2c); //FRAM enter sleep mode (auto-wakeup when identified with Slave Addr)
//Serial number only available for FM24VN10
uint32_t FRAM_Read_Unique_Serial_Num(I2C_HandleTypeDef *hi2c, uint8_t *pData, uint16_t size); //read 8-byte serial number

static HAL_StatusTypeDef I2C_MasterRequestWrite(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, FlagStatus Status, uint32_t Timeout);
static HAL_StatusTypeDef I2C_WaitOnMasterAddressFlagUntilTimeout(I2C_HandleTypeDef *hi2c, uint32_t Flag, uint32_t Timeout);
static HAL_StatusTypeDef I2C1_MasterRequestRead(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Timeout);


#endif
