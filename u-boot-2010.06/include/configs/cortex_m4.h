
/*
 * (C) Copyright 2009, HISILICON
 * Configuation settings for the hi3521a board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_CORTEX_M4_H__
#define __CONFIG_CORTEX_M4_H__

//#include <asm/arch/platform.h>

/* custom define */
/* 128Kb */
#define CONFIG_IMAGE_END			0x20000

#define CONFIG_KERNEL_ADDR			(0x08000000 + CONFIG_IMAGE_END)

/* Enter the table key CMD to complete automatically */
#define CONFIG_AUTO_COMPLETE    	1

/* Use the up / down direction key to call up the history command */
#define CONFIG_CMDLINE_EDITING    	1

#define CONFIG_CMD_SF				1

#define CONFIG_CMD_SAVEENV			1

#define CONFIG_CMD_MEMORY			1
#define CONFIG_SYS_MEMTEST_START    (CFG_DDR_PHYS_OFFSET + sizeof(unsigned long))
#define CONFIG_SYS_MEMTEST_END      (CFG_DDR_PHYS_OFFSET + CFG_DDR_SIZE)
#define CONFIG_SYS_MEMTEST_SCRATCH  (CFG_DDR_PHYS_OFFSET)

#define CONFIG_CMD_MEM_MD			1
#define CONFIG_CMD_MEM_MW			1
#define CONFIG_CMD_MEM_CRC			1
#define CONFIG_CMD_MEM_BASE			1

#define CONFIG_CMDLINE_TAG			1

#define CONFIG_OF_LIBFDT			1
/* Initial Memory map for Linux */
#define CONFIG_SYS_BOOTMAPSZ        0x20000000
#define CONFIG_LMB					1

/* must be set */
/* no nor flash */
#define CONFIG_SYS_NO_FLASH

/* must be set */
/* we have 1 bank of DRAM */
#define CONFIG_NR_DRAM_BANKS		1          

/*-----------------------------------------------------------------------
 *  Environment   Configuration
 *-----------------------------------------------------------------------*/
/* must be set */
#if 0
#define CONFIG_BOOTCOMMAND 			"sf probe 1;sf read 0x20000000 0x00 0x1000;fdt addr 0x20000000;fdt c;xipkernel"
#else
#define CONFIG_BOOTCOMMAND 			"xipkernel"
#endif
#define CONFIG_BOOTDELAY			2
#define CONFIG_BOOTARGS 			"mem=1M@0x68000000 console=ttyAMA0,115200 root=/dev/mtdblock1 rootfstype=romfs mtdparts=cortex_m4_eflash:4K(dtb),256K(rootfs)"
/* talk on MY local net */
#define CONFIG_NETMASK  			255.255.255.0 
/* static IP I currently own */
#define CONFIG_IPADDR   			192.168.1.10 
/* current IP of tftp server ip */
#define CONFIG_SERVERIP 			192.168.1.2     
#define CONFIG_ETHADDR  			00:00:23:34:45:66
/* file to load */
#define CONFIG_BOOTFILE 			"uImage"        
#define CONFIG_BAUDRATE     		115200

/* must be set */
/* include ENV_HEADER_SIZE */
/* 2Kb */
#define CONFIG_ENV_SIZE				(0x800) 
#define CONFIG_ENV_SECT_SIZE		CONFIG_ENV_SIZE

/* must be set */
/* 3Kb */
#define CONFIG_SYS_MALLOC_LEN		(0xC00)

/* must be set */
/* do_printenv  do_setenv common/cmd_nvedit.c */
#define CONFIG_SYS_BAUDRATE_TABLE 	{ 9600, 19200, 38400, 57600, 115200 }
/* max number of command args */
#define CONFIG_SYS_MAXARGS 			32          

/* must be set */
/* common/cmd_load.c:445:  offset = CONFIG_SYS_LOAD_ADDR; */
#define CONFIG_SYS_LOAD_ADDR 		(0x68000000)

/* must be set */
#define CONFIG_ENV_IS_IN_SPI_FLASH

/* must be set */
/*-----------------------------------------------------------------------
 * console display  Configuration
 ------------------------------------------------------------------------*/
/* used in common/main.c */
#define CONFIG_VERSION_VARIABLE  	1 
/* Monitor Command Prompt */
#define CONFIG_SYS_PROMPT  			"cortex-m4 # "	
/* Console I/O Buffer Size */
#define CONFIG_SYS_CBSIZE  			1024            
#define CONFIG_SYS_PBSIZE  			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/* must be set */
/* env in flash instead of CFG_ENV_IS_NOWHERE */
/* environment starts here */
#define CONFIG_ENV_OFFSET			(CONFIG_IMAGE_END - CONFIG_ENV_SIZE)    

/* must be set */
/* kernel parameter list phy addr */
//#define MEM_BASE_DDR				(DDR_MEM_BASE)
/* board/cortex_m4/board.c:111:    gd->bd->bi_boot_params = CFG_BOOT_PARAMS; */
/* 256b */
#define CFG_BOOT_PARAMS				(0x20000000)

/* must be set */
/* board/cortex_m4/board.c:99 */
#define CFG_DDR_PHYS_OFFSET 		(0x20000000)

/* must be set */
/* 192Kb */
/* board/cortex_m4/board.c:100 */
#define CFG_DDR_SIZE				(192 * 1024UL) 

/* must be set (to do)*/
//#define CONFIG_SPI_FLASH

//timer(to do)
/* how many ticks per second. show the precision of timer */
//#define CONFIG_SYS_HZ           	(72000000)
#define CONFIG_SYS_HZ           	(1000)

#define CONFIG_CMD_LOADB			1	

#endif	/* __CONFIG_H */

