#include "internal_flash.h"

#define FLASH_BASE 0x08000000
#define FLASH_WAITETIME  50000

#define ADDR_FLASH_SECTOR_0     ((u32)0x08000000) 
#define ADDR_FLASH_SECTOR_1     ((u32)0x08004000)
#define ADDR_FLASH_SECTOR_2     ((u32)0x08008000)
#define ADDR_FLASH_SECTOR_3     ((u32)0x0800C000) 
#define ADDR_FLASH_SECTOR_4     ((u32)0x08010000)
#define ADDR_FLASH_SECTOR_5     ((u32)0x08020000)
#define ADDR_FLASH_SECTOR_6     ((u32)0x08040000)
#define ADDR_FLASH_SECTOR_7     ((u32)0x08060000)
#define ADDR_FLASH_SECTOR_8     ((u32)0x08080000)
#define ADDR_FLASH_SECTOR_9     ((u32)0x080A0000)
#define ADDR_FLASH_SECTOR_10    ((u32)0x080C0000)
#define ADDR_FLASH_SECTOR_11    ((u32)0x080E0000)

u32 STMFLASH_ReadWord(u32 faddr)
{
	return *(volatile u32 *)faddr; 
}

void STMFLASH_Read(u32 raddr, u32 *buffer, u32 nread)
{
	u32 i;
	for (i = 0; i < nread; i++)
	{
		buffer[i] = STMFLASH_ReadWord(raddr);
		raddr += 4;
	}
}

u8 STMFLASH_GetFlashSector(u32 addr)
{
	if (addr < ADDR_FLASH_SECTOR_1) return FLASH_SECTOR_0;
	else if (addr < ADDR_FLASH_SECTOR_2) return FLASH_SECTOR_1;
	else if (addr < ADDR_FLASH_SECTOR_3) return FLASH_SECTOR_2;
	else if (addr < ADDR_FLASH_SECTOR_4) return FLASH_SECTOR_3;
	else if (addr < ADDR_FLASH_SECTOR_5) return FLASH_SECTOR_4;
	else if (addr < ADDR_FLASH_SECTOR_6) return FLASH_SECTOR_5;
	else if (addr < ADDR_FLASH_SECTOR_7) return FLASH_SECTOR_6;
	else if (addr < ADDR_FLASH_SECTOR_8) return FLASH_SECTOR_7;
	else if (addr < ADDR_FLASH_SECTOR_9) return FLASH_SECTOR_8;
	else if (addr < ADDR_FLASH_SECTOR_10) return FLASH_SECTOR_9;
	else if (addr < ADDR_FLASH_SECTOR_11) return FLASH_SECTOR_10;   
	return FLASH_SECTOR_11;	
}

void STMFLASH_Write(u32 waddr, u32 *buffer, u32 nwrite)
{ 
	FLASH_EraseInitTypeDef FlashEraseInit;
	HAL_StatusTypeDef FlashStatus = HAL_OK;
	u32 SectorError = 0;
	u32 addrx = 0;
	u32 endaddr = 0;
	if (waddr < FLASH_BASE || waddr % 4)
		return;

	HAL_FLASH_Unlock();
	FLASH_WaitForLastOperation(FLASH_WAITETIME); 
	
	addrx = waddr;
	endaddr = waddr + nwrite * 4;

	if (addrx < 0x1FFF0000)
	{
		while (addrx < endaddr)
		{
			if (STMFLASH_ReadWord(addrx) != 0xFFFFFFFF)
			{   
				FlashEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
				FlashEraseInit.Sector = STMFLASH_GetFlashSector(addrx);
				FlashEraseInit.NbSectors = 1;
				FlashEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;
				if (HAL_FLASHEx_Erase(&FlashEraseInit, &SectorError) != HAL_OK) 
				{
					printf("erase sector: %d failed\n", FlashEraseInit.Sector);
					break;
				}
			} 
			else 
			{
				addrx += 4;
			}
			FLASH_WaitForLastOperation(FLASH_WAITETIME);
		}
	}
	FlashStatus = FLASH_WaitForLastOperation(FLASH_WAITETIME);
	if (FlashStatus == HAL_OK)
	{
		while (waddr < endaddr)
		{
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, waddr, *buffer) != HAL_OK)
			{ 
				printf("write addr: 0x%x failed\n", waddr);
				break;
			}
			waddr += 4;
			buffer++;
		}  
	}
	HAL_FLASH_Lock();
} 

int internal_flash_probe(struct spi_flash *flash)
{
	return 0;
}

int internal_flash_read(struct spi_flash *flash, u32 offset, size_t len, void *buf)
{
	debug("%s read offset: 0x%x len: 0x%x buf: 0x%x\n", flash->name, offset, len, buf);
	STMFLASH_Read(FLASH_BASE + offset, buf, len / 4);
	return 0;
}

int internal_flash_write(struct spi_flash *flash, u32 offset, size_t len, const void *buf)
{
	debug("%s write offset: 0x%x len: 0x%x buf: 0x%x\n", flash->name, offset, len, buf);
	STMFLASH_Write(FLASH_BASE + offset, buf, len / 4);
	return 0;
}

int internal_flash_erase(struct spi_flash *flash, u32 offset, size_t len)
{
	debug("%s erase offset: 0x%x len: 0x%x\n", flash->name, offset, len);
	return 0;
}
