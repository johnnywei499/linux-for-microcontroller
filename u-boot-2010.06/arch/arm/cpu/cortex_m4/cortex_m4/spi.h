#ifndef _SPI_H
#define _SPI_H
#include <common.h>
#include <spi.h>
#include <spi_flash.h>
#include "stm32f4xx_hal.h"

void SPI_Init(void);

void SPI_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI_ReadWriteByte(u8 TxData);

#endif

