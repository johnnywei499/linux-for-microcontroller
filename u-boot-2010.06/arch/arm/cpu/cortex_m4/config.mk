#
# (C) Copyright 2002
# Gary Jennejohn, DENX Software Engineering, <garyj@denx.de>
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

STANDALONE_LOAD_ADDR = 0x68000000

######################################
# building variables
######################################
# debug build?
# DEBUG = 1
# optimization
# OPT = -Og

#######################################
# CFLAGS
#######################################
# cpu
CUR_CPU = -mcpu=cortex-m4

# fpu
# FPU = -mfpu=fpv4-sp-d16

# float-abi
# FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CUR_CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32F407xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-I$(TOPDIR)/$(CPUDIR)/$(SOC)/Core/Inc \
-I$(TOPDIR)/$(CPUDIR)/$(SOC)/Drivers/STM32F4xx_HAL_Driver/Inc \
-I$(TOPDIR)/$(CPUDIR)/$(SOC)/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy \
-I$(TOPDIR)/$(CPUDIR)/$(SOC)/Drivers/CMSIS/Device/ST/STM32F4xx/Include \
-I$(TOPDIR)/$(CPUDIR)/$(SOC)/Drivers/CMSIS/Include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) #-Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) #-Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
# CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

PLATFORM_RELFLAGS += -fno-common -ffixed-r8 $(CFLAGS)

# Make Cortex M4 to allow more compilers to work, even though its v7m.
# PLATFORM_CPPFLAGS += -march=armv7-m

# =========================================================================
#
# Supply options according to compiler version
#
# =========================================================================
PLATFORM_RELFLAGS +=$(call cc-option,-mshort-load-bytes,$(call cc-option,-malignment-traps,))
