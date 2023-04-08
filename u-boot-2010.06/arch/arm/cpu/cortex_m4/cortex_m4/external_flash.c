#include "external_flash.h"
#include "spi.h"
#include "sys.h"

#define W25Q80 		0XEF13
#define W25Q16 		0XEF14
#define W25Q32 		0XEF15
#define W25Q64 		0XEF16
#define W25Q128		0XEF17
#define W25Q256 	0XEF18

#define NM25Q80		0X5213
#define NM25Q16		0X5214
#define NM25Q32		0X5215
#define NM25Q64		0X5216
#define NM25Q128	0X5217
#define NM25Q256	0X5218

#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg1		0x05 
#define W25X_ReadStatusReg2		0x35 
#define W25X_ReadStatusReg3		0x15 
#define W25X_WriteStatusReg1    0x01 
#define W25X_WriteStatusReg2    0x31 
#define W25X_WriteStatusReg3    0x11 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 
#define W25X_Enable4ByteAddr    0xB7
#define W25X_Exit4ByteAddr      0xE9

void W25QXX_Init(void);
u16 W25QXX_ReadID(void);
u8 W25QXX_ReadSR(u8 regno);
void W25QXX_4ByteAddr_Enable(void);     
void W25QXX_Write_SR(u8 regno, u8 sr);
void W25QXX_Write_Enable(void);  		
void W25QXX_Write_Disable(void);
void W25QXX_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void W25QXX_Read(u8 *pBuffer, u32 ReadAddr, u16 NumByteToRead);
void W25QXX_Write(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite);
void W25QXX_Erase_Chip(void);
void W25QXX_Erase_Sector(u32 Dst_Addr);
void W25QXX_Wait_Busy(void);
void W25QXX_PowerDown(void);
void W25QXX_WAKEUP(void);

#define	W25QXX_CS PBout(14)
u16 W25QXX_TYPE = W25Q256;

void W25QXX_Init(void)
{ 
	u8 temp;
	GPIO_InitTypeDef GPIO_Initure;

	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_Initure.Pin  = GPIO_PIN_14;
	GPIO_Initure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Initure.Pull = GPIO_PULLUP;
	GPIO_Initure.Speed = GPIO_SPEED_HIGH;      
	HAL_GPIO_Init(GPIOB, &GPIO_Initure);

	W25QXX_CS = 1;
	//SPI1_Init();
	SPI_SetSpeed(SPI_BAUDRATEPRESCALER_4);
	W25QXX_TYPE = W25QXX_ReadID();
	if (W25QXX_TYPE == W25Q256)
	{
		temp = W25QXX_ReadSR(3);
		if ((temp & 0x01) == 0)
		{
			W25QXX_CS = 0;
			SPI_ReadWriteByte(W25X_Enable4ByteAddr); 
			W25QXX_CS = 1;
		}
	}
}  

u8 W25QXX_ReadSR(u8 regno)   
{  
	u8 byte = 0, command = 0; 
	switch (regno)
	{
		case 1:
			command = W25X_ReadStatusReg1;
			break;
		case 2:
			command = W25X_ReadStatusReg2;
			break;
		case 3:
			command = W25X_ReadStatusReg3;
			break;
		default:
			command = W25X_ReadStatusReg1;    
			break;
	}    
	W25QXX_CS = 0;
	SPI_ReadWriteByte(command);
	byte = SPI_ReadWriteByte(0xff);
	W25QXX_CS = 1;
	return byte;   
} 

void W25QXX_Write_SR(u8 regno, u8 sr)   
{   
    u8 command = 0;
    switch (regno)
    {
        case 1:
            command = W25X_WriteStatusReg1;
            break;
        case 2:
            command = W25X_WriteStatusReg2;
            break;
        case 3:
            command = W25X_WriteStatusReg3;
            break;
        default:
            command = W25X_WriteStatusReg1;    
            break;
    }   
	W25QXX_CS = 0;
	SPI_ReadWriteByte(command);
	SPI_ReadWriteByte(sr);
	W25QXX_CS = 1;
}   

void W25QXX_Write_Enable(void)   
{
	W25QXX_CS = 0;
    SPI_ReadWriteByte(W25X_WriteEnable);
	W25QXX_CS = 1;   	      
} 

void W25QXX_Write_Disable(void)   
{  
	W25QXX_CS = 0;
    SPI_ReadWriteByte(W25X_WriteDisable); 
	W25QXX_CS = 1;
} 

u16 W25QXX_ReadID(void)
{
	u16 Temp = 0;	  
	W25QXX_CS = 0;				    
	SPI_ReadWriteByte(0x90);  
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 	    
	SPI_ReadWriteByte(0x00); 	 			   
	Temp |= SPI_ReadWriteByte(0xFF) << 8;  
	Temp |= SPI_ReadWriteByte(0xFF);	 
	W25QXX_CS = 1;				    
	return Temp;
}   		    

void W25QXX_Read(u8 *pBuffer, u32 ReadAddr, u16 NumByteToRead)   
{ 
 	u16 i;   										    
	W25QXX_CS = 0; 
    SPI_ReadWriteByte(W25X_ReadData);
    if (W25QXX_TYPE == W25Q256)
    {
        SPI_ReadWriteByte((u8)((ReadAddr) >> 24));    
    }
    SPI_ReadWriteByte((u8)((ReadAddr) >> 16));
    SPI_ReadWriteByte((u8)((ReadAddr) >> 8));   
    SPI_ReadWriteByte((u8)ReadAddr);   
    for (i = 0; i < NumByteToRead; i++)
	{ 
        pBuffer[i] = SPI_ReadWriteByte(0xFF);
    }
	W25QXX_CS = 1;  				    	      
}  

void W25QXX_Write_Page(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)
{
 	u16 i;  
    W25QXX_Write_Enable();
	W25QXX_CS = 0;  
    SPI_ReadWriteByte(W25X_PageProgram); 
    if (W25QXX_TYPE == W25Q256)
    {
        SPI_ReadWriteByte((u8)((WriteAddr) >> 24)); 
    }
    SPI_ReadWriteByte((u8)((WriteAddr) >> 16));
    SPI_ReadWriteByte((u8)((WriteAddr) >> 8));   
    SPI_ReadWriteByte((u8)WriteAddr);   
    for (i = 0; i < NumByteToWrite; i++)
		SPI_ReadWriteByte(pBuffer[i]);
	W25QXX_CS = 1;
	W25QXX_Wait_Busy();
} 

void W25QXX_Write_NoCheck(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain = 256 - WriteAddr % 256;
	if (NumByteToWrite <= pageremain)
		pageremain = NumByteToWrite;
	while (1)
	{	   
		W25QXX_Write_Page(pBuffer, WriteAddr, pageremain);
		if (NumByteToWrite == pageremain) {
			break;
		} else {
			pBuffer += pageremain;
			WriteAddr += pageremain;	

			NumByteToWrite -= pageremain;
			if (NumByteToWrite > 256)
				pageremain = 256;
			else 
				pageremain = NumByteToWrite;
		}
	}    
} 
 
u8 W25QXX_BUFFER[4096];		 
void W25QXX_Write(u8 *pBuffer, u32 WriteAddr, u16 NumByteToWrite)   
{ 
	u32 secpos;
	u16 secoff;
	u16 secremain;	   
 	u16 i;    
	u8 *W25QXX_BUF;	  
   	W25QXX_BUF = W25QXX_BUFFER;	     
 	secpos = WriteAddr / 4096;
	secoff = WriteAddr % 4096;
	secremain = 4096 - secoff;
	
 	if (NumByteToWrite <= secremain)
		secremain = NumByteToWrite;
	
	while (1) 
	{	
		W25QXX_Read(W25QXX_BUF, secpos * 4096, 4096);
		for (i = 0; i < secremain; i++)
		{
			if (W25QXX_BUF[secoff + i] != 0xFF)
				break;
		}
		if (i < secremain) {
			W25QXX_Erase_Sector(secpos);
			for (i = 0; i < secremain; i++)
			{
				W25QXX_BUF[i + secoff] = pBuffer[i];	  
			}
			W25QXX_Write_NoCheck(W25QXX_BUF, secpos * 4096, 4096);

		} else {
			W25QXX_Write_NoCheck(pBuffer, WriteAddr, secremain);
		}
		if (NumByteToWrite == secremain) {
			break;
		} else {
			secpos++;
			secoff = 0;

		   	pBuffer += secremain;
			WriteAddr += secremain;
		   	NumByteToWrite -= secremain;
			if (NumByteToWrite > 4096)
				secremain = 4096;
			else 
				secremain = NumByteToWrite;
		}	 
	};	 
}

void W25QXX_Erase_Chip(void)   
{                                   
    W25QXX_Write_Enable();
    W25QXX_Wait_Busy();   
  	W25QXX_CS = 0;
    SPI_ReadWriteByte(W25X_ChipErase);
	W25QXX_CS = 1;    
	W25QXX_Wait_Busy();
}   

void W25QXX_Erase_Sector(u32 Dst_Addr)   
{  
 	Dst_Addr *= 4096;
    W25QXX_Write_Enable();	 
    W25QXX_Wait_Busy();   
  	W25QXX_CS = 0;  
    SPI_ReadWriteByte(W25X_SectorErase);
    if (W25QXX_TYPE == W25Q256)
    {
        SPI_ReadWriteByte((u8)((Dst_Addr) >> 24)); 
    }
    SPI_ReadWriteByte((u8)((Dst_Addr) >> 16));  
    SPI_ReadWriteByte((u8)((Dst_Addr) >> 8));   
    SPI_ReadWriteByte((u8)Dst_Addr);  
	W25QXX_CS = 1;   	      
    W25QXX_Wait_Busy();
}  

void W25QXX_Wait_Busy(void)   
{   
	while ((W25QXX_ReadSR(1) & 0x01) == 0x01);
}  

void W25QXX_PowerDown(void)   
{ 
  	W25QXX_CS = 0;
    SPI_ReadWriteByte(W25X_PowerDown);
	W25QXX_CS = 1;      
}   

void W25QXX_WAKEUP(void)   
{  
  	W25QXX_CS = 0;
    SPI_ReadWriteByte(W25X_ReleasePowerDown);
	W25QXX_CS = 1;     
}   

#define W25QXX_PAGE_SIZE			4096

int external_flash_probe(struct spi_flash *flash)
{
	W25QXX_Init();
	return 0;
}

int external_flash_read(struct spi_flash *flash, u32 offset, size_t len, void *buf)
{
	int sect;
	debug("%s read offset: 0x%x len: 0x%x buf: 0x%x\n", flash->name, offset, len, buf);
	if ((offset % W25QXX_PAGE_SIZE != 0) || (len % W25QXX_PAGE_SIZE != 0)) {
		printf("offset: 0x%x len: 0x%x failed\n", offset, len);
		return 0;
	}
	for (sect = 0; sect < len / W25QXX_PAGE_SIZE; sect++) {
		printf("\33[2K\r");
		printf("read: %d%%", sect * 100 / (len / W25QXX_PAGE_SIZE));
		W25QXX_Read(buf + sect * W25QXX_PAGE_SIZE, offset + sect * W25QXX_PAGE_SIZE, W25QXX_PAGE_SIZE);
	}
	printf("\33[2K\r");
	printf("read: %d%%\n", 100);
	return 0;
}


int external_flash_write(struct spi_flash *flash, u32 offset, size_t len, const void *buf)
{
	int sect;
	debug("%s write offset: 0x%x len: 0x%x buf: 0x%x\n", flash->name, offset, len, buf);
	if ((offset % W25QXX_PAGE_SIZE != 0) || (len % W25QXX_PAGE_SIZE != 0)) {
		printf("offset: 0x%x len: 0x%x failed\n", offset, len);
		return 0;
	}
	for (sect = 0; sect < len / W25QXX_PAGE_SIZE; sect++) {
		printf("\33[2K\r");
		printf("write: %d%%", sect * 100 / (len / W25QXX_PAGE_SIZE));
		W25QXX_Erase_Sector(offset / W25QXX_PAGE_SIZE + sect);
		W25QXX_Write_NoCheck(buf + sect * W25QXX_PAGE_SIZE, offset + sect * W25QXX_PAGE_SIZE, W25QXX_PAGE_SIZE);//写入整个扇区 
	}
	printf("\33[2K\r");
	printf("write: %d%%\n", 100);
	return 0;
}

int external_flash_erase(struct spi_flash *flash, u32 offset, size_t len)
{
	int sect;
	debug("%s write offset: 0x%x len: 0x%x\n", flash->name, offset, len);
	if ((offset % W25QXX_PAGE_SIZE != 0) || (len % W25QXX_PAGE_SIZE != 0)) {
		printf("offset: 0x%x len: 0x%x failed\n", offset, len);
		return 0;
	}
	for (sect = 0; sect < len / W25QXX_PAGE_SIZE; sect++) {
		printf("\33[2K\r");
		printf("erase: %d%%", sect * 100 / (len / W25QXX_PAGE_SIZE));
		W25QXX_Erase_Sector(offset / W25QXX_PAGE_SIZE + sect);
	}
	printf("\33[2K\r");
	printf("erase: %d%%\n", 100);
	return 0;
}


