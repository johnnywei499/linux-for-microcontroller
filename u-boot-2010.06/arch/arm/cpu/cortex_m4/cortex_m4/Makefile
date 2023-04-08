#
# (C) Copyright 2000-2003
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

include $(TOPDIR)/config.mk

LIB	=  $(obj)lib$(SOC).a

SOBJS	+= 

COBJS	+= reset.o it.o gpio.o spi.o clock.o timer.o uart.o hal.o flash.o internal_flash.o external_flash.o sram.o

#COBJS	+= Core/Src/main.o
#COBJS	+= Core/Src/stm32f4xx_it.o
#COBJS	+= Core/Src/stm32f4xx_hal_msp.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.o
COBJS	+= Core/Src/system_stm32f4xx.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_fsmc.o
COBJS	+= Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_sram.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS:.o=.c)
OBJS	:= $(addprefix $(obj),$(COBJS) $(SOBJS))

all:	 $(obj).depend $(LIB)

$(LIB):	$(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
