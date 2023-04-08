/*
 * armboot - Startup Code for OMAP3530/ARM Cortex CPU-core
 *
 * Copyright (c) 2004	Texas Instruments <r-woodruff2@ti.com>
 *
 * Copyright (c) 2001	Marius Gröger <mag@sysgo.de>
 * Copyright (c) 2002	Alex Züpke <azu@sysgo.de>
 * Copyright (c) 2002	Gary Jennejohn <garyj@denx.de>
 * Copyright (c) 2003	Richard Woodruff <r-woodruff2@ti.com>
 * Copyright (c) 2003	Kshitij <kshitij@ti.com>
 * Copyright (c) 2006-2008 Syed Mohammed Khasim <x0khasim@ti.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
 
#include <config.h>
#include <version.h>

/*
 *************************************************************************
 *
 * Jump vector table as in table 3.1 in [1]
 *
 *************************************************************************
 */
 
.syntax unified
.cpu cortex-m4
.fpu softvfp
.thumb

.globl _start
_start:
	b reset

_TEXT_BASE:
	.word TEXT_BASE

.globl _armboot_start
_armboot_start:
	@.word _start
	.word __data_start

.globl _bss_start
_bss_start:
	.word __bss_start

.globl _bss_end
_bss_end:
	.word __bss_end

_start_armboot: 
	.word start_armboot

_stack_end:
	.word __stack_end

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called.
 * @param  None
 * @retval : None
*/

.weak reset
.type reset, %function
.size reset, .-reset
reset:
	/* Copy the data segment initializers from flash to SRAM */
	ldr r0, =__data_start
	ldr r1, =__data_end
	ldr r2, =__sidata
	sub r3, r0, r2
	/* check whether LOADADDR is the same as the running address */
	cmp r3, #0x20000
	ble LC1
	
	movs r3, #0
	b LoopCopyDataInit

CopyDataInit:
	ldr r4, [r2, r3]
	str r4, [r0, r3]
	adds r3, r3, #4

LoopCopyDataInit:
	adds r4, r0, r3
	cmp r4, r1
	bcc CopyDataInit

LC1:	
	/* Zero fill the bss segment. */
	ldr r2, =__bss_start
	ldr r4, =__bss_end
	movs r3, #0
	b LoopFillZerobss

FillZerobss:
	str  r3, [r2]
	adds r2, r2, #4

LoopFillZerobss:
	cmp r2, r4
	bcc FillZerobss
  
	ldr sp, =__stack_end
	bl hal_init				@CPU/PLL/NVIC Initialize 
	bl start_armboot		@jump to C code

/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
.section .isr_vector,"a",%progbits
.type g_pfnVectors, %object
.size g_pfnVectors, .-g_pfnVectors
g_pfnVectors:
	.word  __stack_end
	.word  Reset_Handler
	.word  NMI_Handler
	.word  HardFault_Handler
	.word  MemManage_Handler
	.word  BusFault_Handler
	.word  UsageFault_Handler
	.word  0
	.word  0
	.word  0
	.word  0
	.word  SVC_Handler
	.word  DebugMon_Handler
	.word  0
	.word  PendSV_Handler
	.word  SysTick_Handler

	/* External Interrupts */
	.word     WWDG_IRQHandler                   /* Window WatchDog              */                                        
	.word     PVD_IRQHandler                    /* PVD through EXTI Line detection */                        
	.word     TAMP_STAMP_IRQHandler             /* Tamper and TimeStamps through the EXTI line */            
	.word     RTC_WKUP_IRQHandler               /* RTC Wakeup through the EXTI line */                      
	.word     FLASH_IRQHandler                  /* FLASH                        */                                          
	.word     RCC_IRQHandler                    /* RCC                          */                                            
	.word     EXTI0_IRQHandler                  /* EXTI Line0                   */                        
	.word     EXTI1_IRQHandler                  /* EXTI Line1                   */                          
	.word     EXTI2_IRQHandler                  /* EXTI Line2                   */                          
	.word     EXTI3_IRQHandler                  /* EXTI Line3                   */                          
	.word     EXTI4_IRQHandler                  /* EXTI Line4                   */                          
	.word     DMA1_Stream0_IRQHandler           /* DMA1 Stream 0                */                  
	.word     DMA1_Stream1_IRQHandler           /* DMA1 Stream 1                */                   
	.word     DMA1_Stream2_IRQHandler           /* DMA1 Stream 2                */                   
	.word     DMA1_Stream3_IRQHandler           /* DMA1 Stream 3                */                   
	.word     DMA1_Stream4_IRQHandler           /* DMA1 Stream 4                */                   
	.word     DMA1_Stream5_IRQHandler           /* DMA1 Stream 5                */                   
	.word     DMA1_Stream6_IRQHandler           /* DMA1 Stream 6                */                   
	.word     ADC_IRQHandler                    /* ADC1, ADC2 and ADC3s         */                   
	.word     CAN1_TX_IRQHandler                /* CAN1 TX                      */                         
	.word     CAN1_RX0_IRQHandler               /* CAN1 RX0                     */                          
	.word     CAN1_RX1_IRQHandler               /* CAN1 RX1                     */                          
	.word     CAN1_SCE_IRQHandler               /* CAN1 SCE                     */                          
	.word     EXTI9_5_IRQHandler                /* External Line[9:5]s          */                          
	.word     TIM1_BRK_TIM9_IRQHandler          /* TIM1 Break and TIM9          */         
	.word     TIM1_UP_TIM10_IRQHandler          /* TIM1 Update and TIM10        */         
	.word     TIM1_TRG_COM_TIM11_IRQHandler     /* TIM1 Trigger and Commutation and TIM11 */
	.word     TIM1_CC_IRQHandler                /* TIM1 Capture Compare         */                          
	.word     TIM2_IRQHandler                   /* TIM2                         */                   
	.word     TIM3_IRQHandler                   /* TIM3                         */                   
	.word     TIM4_IRQHandler                   /* TIM4                         */                   
	.word     I2C1_EV_IRQHandler                /* I2C1 Event                   */                          
	.word     I2C1_ER_IRQHandler                /* I2C1 Error                   */                          
	.word     I2C2_EV_IRQHandler                /* I2C2 Event                   */                          
	.word     I2C2_ER_IRQHandler                /* I2C2 Error                   */                            
	.word     SPI1_IRQHandler                   /* SPI1                         */                   
	.word     SPI2_IRQHandler                   /* SPI2                         */                   
	.word     USART1_IRQHandler                 /* USART1                       */                   
	.word     USART2_IRQHandler                 /* USART2                       */                   
	.word     USART3_IRQHandler                 /* USART3                       */                   
	.word     EXTI15_10_IRQHandler              /* External Line[15:10]s        */                          
	.word     RTC_Alarm_IRQHandler              /* RTC Alarm (A and B) through EXTI Line */                 
	.word     OTG_FS_WKUP_IRQHandler            /* USB OTG FS Wakeup through EXTI line */                       
	.word     TIM8_BRK_TIM12_IRQHandler         /* TIM8 Break and TIM12         */         
	.word     TIM8_UP_TIM13_IRQHandler          /* TIM8 Update and TIM13        */         
	.word     TIM8_TRG_COM_TIM14_IRQHandler     /* TIM8 Trigger and Commutation and TIM14 */
	.word     TIM8_CC_IRQHandler                /* TIM8 Capture Compare         */                          
	.word     DMA1_Stream7_IRQHandler           /* DMA1 Stream7                 */                          
	.word     FSMC_IRQHandler                   /* FSMC                         */                   
	.word     SDIO_IRQHandler                   /* SDIO                         */                   
	.word     TIM5_IRQHandler                   /* TIM5                         */                   
	.word     SPI3_IRQHandler                   /* SPI3                         */                   
	.word     UART4_IRQHandler                  /* UART4                        */                   
	.word     UART5_IRQHandler                  /* UART5                        */                   
	.word     TIM6_DAC_IRQHandler               /* TIM6 and DAC1&2 underrun errors */                   
	.word     TIM7_IRQHandler                   /* TIM7                         */
	.word     DMA2_Stream0_IRQHandler           /* DMA2 Stream 0                */                   
	.word     DMA2_Stream1_IRQHandler           /* DMA2 Stream 1                */                   
	.word     DMA2_Stream2_IRQHandler           /* DMA2 Stream 2                */                   
	.word     DMA2_Stream3_IRQHandler           /* DMA2 Stream 3                */                   
	.word     DMA2_Stream4_IRQHandler           /* DMA2 Stream 4                */                   
	.word     ETH_IRQHandler                    /* Ethernet                     */                   
	.word     ETH_WKUP_IRQHandler               /* Ethernet Wakeup through EXTI line */                     
	.word     CAN2_TX_IRQHandler                /* CAN2 TX                      */                          
	.word     CAN2_RX0_IRQHandler               /* CAN2 RX0                     */                          
	.word     CAN2_RX1_IRQHandler               /* CAN2 RX1                     */                          
	.word     CAN2_SCE_IRQHandler               /* CAN2 SCE                     */                          
	.word     OTG_FS_IRQHandler                 /* USB OTG FS                   */                   
	.word     DMA2_Stream5_IRQHandler           /* DMA2 Stream 5                */                   
	.word     DMA2_Stream6_IRQHandler           /* DMA2 Stream 6                */                   
	.word     DMA2_Stream7_IRQHandler           /* DMA2 Stream 7                */                   
	.word     USART6_IRQHandler                 /* USART6                       */                    
	.word     I2C3_EV_IRQHandler                /* I2C3 event                   */                          
	.word     I2C3_ER_IRQHandler                /* I2C3 error                   */                          
	.word     OTG_HS_EP1_OUT_IRQHandler         /* USB OTG HS End Point 1 Out   */                   
	.word     OTG_HS_EP1_IN_IRQHandler          /* USB OTG HS End Point 1 In    */                   
	.word     OTG_HS_WKUP_IRQHandler            /* USB OTG HS Wakeup through EXTI */                         
	.word     OTG_HS_IRQHandler                 /* USB OTG HS                   */                   
	.word     DCMI_IRQHandler                   /* DCMI                         */                   
	.word     0                                 /* CRYP crypto                  */                   
	.word     HASH_RNG_IRQHandler               /* Hash and Rng                 */
	.word     FPU_IRQHandler                    /* FPU                          */

.type Reset_Handler, %function
.size Reset_Handler, .-Reset_Handler
Reset_Handler:

relocate:
	/* check if relocation to sram is required */
	ldr	r0, =__isr_end
	ldr	r1, =TEXT_BASE
	sub r3, r1, r0
	cmp r3, #0x100000
	ble LC0
	
	ldr r3, =__bss_start
	sub	r2, r3, r1
	add r2, r0, r2

.type copy_to_sdram, %function
.size copy_to_sdram, .-copy_to_sdram
copy_to_sdram:
	ldmia   r0!, {r3 - r6}
	stmia   r1!, {r3 - r6}
	cmp     r0, r2
	ble     copy_to_sdram
LC0:
	bl reset
	