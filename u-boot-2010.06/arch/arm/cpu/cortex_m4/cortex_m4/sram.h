#ifndef _SRAM_H
#define _SRAM_H
#include <common.h>
#include "stm32f4xx_hal.h"

void SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8 *pBuffer, u32 WriteAddr, u32 n);
void FSMC_SRAM_ReadBuffer(u8 *pBuffer, u32 ReadAddr, u32 n);

#endif
