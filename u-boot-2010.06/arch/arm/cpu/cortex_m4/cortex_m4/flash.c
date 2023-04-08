/*
 * SPI flash interface
 *
 * Copyright (C) 2008 Atmel Corporation
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <malloc.h>
#include <spi.h>
#include <spi_flash.h>
#include "internal_flash.h"
#include "external_flash.h"

struct spi_flash flashs[2] = {
	{
		.name = "internal_flash",
		.size = (1 * 1024 * 1024),
		.read = internal_flash_read,
		.write = internal_flash_write,
		.erase = internal_flash_erase,
	},
	{
		.name = "extern_flash",
		.size = (16 * 1024 * 1024),
		.read = external_flash_read,
		.write = external_flash_write,
		.erase = external_flash_erase,
	},
};

int spi_flash_cmd(struct spi_slave *spi, u8 cmd, void *response, size_t len)
{
	return 0;
}

int spi_flash_cmd_read(struct spi_slave *spi, const u8 *cmd,
		size_t cmd_len, void *data, size_t data_len)
{
	return 0;
}

int spi_flash_cmd_write(struct spi_slave *spi, const u8 *cmd, size_t cmd_len,
		const void *data, size_t data_len)
{
	return 0;
}


int spi_flash_read_common(struct spi_flash *flash, const u8 *cmd,
		size_t cmd_len, void *data, size_t data_len)
{
	return 0;
}

struct spi_flash *spi_flash_probe(unsigned int bus, unsigned int cs,
		unsigned int max_hz, unsigned int spi_mode)
{
	struct spi_slave *spi;
	struct spi_flash *flash = NULL;

	debug("bus: %d cs: %d max_hz: %d spi_mode: %d\n", bus, cs, max_hz, spi_mode);

	if (cs != 0 && cs != 1)
		return NULL;
	
	flash = &flashs[cs];
	if (cs == 0) {
		internal_flash_probe(flash);
	} else if(cs == 1) {
		external_flash_probe(flash);
	}
	return flash;
}

void spi_flash_free(struct spi_flash *flash)
{
	
}
