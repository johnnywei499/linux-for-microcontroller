#ifndef _INTERNAL_FLASH_H
#define _INTERNAL_FLASH_H
#include <common.h>
#include <spi.h>
#include <spi_flash.h>
#include "stm32f4xx_hal.h"

int internal_flash_probe(struct spi_flash *flash);
int internal_flash_read(struct spi_flash *flash, u32 offset, size_t len, void *buf);
int internal_flash_write(struct spi_flash *flash, u32 offset, size_t len, const void *buf);
int internal_flash_erase(struct spi_flash *flash, u32 offset, size_t len);

#endif
