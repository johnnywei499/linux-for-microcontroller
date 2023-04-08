# project description
This is a linux-3.12.74 project that can run on an STM32F407 with only 1MB of memory. It also provides a complete description of the software and hardware environment required to run this project.

***The source code will be uploaded later.***

For more information, please contact email johnnywei499@gmail.com



## 1、Why port Linux to microcontrollers

The Linux source code is very large and complex, which makes it challenging for beginners who want to study it. The processing of armv7 and armv8 architecture CPUs in Linux is also very complex. In contrast, microcontrollers have simple functionalities and can provide the most basic operating environment required by Linux. By using a microcontroller, developers can build the simplest running environment for Linux. This project can help developers understand the boot process of u-boot, Linux, and rootfs, as well as subsystems such as process management, memory management, interrupt management, and driver management.



## 2、Why did you choose the stm32f407 microcontroller for this project

The reason for choosing the STM32F407 microcontroller is that it belongs to the armv7m architecture, and its hardware documentation is comprehensive, allowing developers to focus on software implementation of the operating system without spending a lot of time debugging hardware.



# hardware environment

## 1、SOC

+ cpu：	    stm32f407zgt6
+ ram：       128KB
+ rom：       1MB
+ sdram：   1MB
+ spi flash：16MB



## 2、board

![](https://github.com/johnnywei499/linux-for-mcu/blob/main/doc/board.png)

**Statement: I have no affiliation with the merchant. I simply purchased their development board on Taobao, and I will provide a link for reference.**

【淘宝】https://m.tb.cn/h.UIACPhs?tk=07kkdkzmXYw CZ3457 「正点原子STM32F407ZGT6小系统板 核心板ARM开发板STM32F4单片机」
点击链接直接打开 或者 淘宝搜索直接打开


## 3、serial terminal tool

SecureCRT

**SecureCRT can also be used as a tool for upgrading kernel, device tree, and root file system**



## 4、Hardware connection

+ burning the serial port：USART1 (PA9/PA10) --> usb port
+ console the serial port：USART2 (PA2/PA3)   --> debug serial



# How to compile this project

## 1、Compile u-boot

``make boot_config``

``make boot``



## 2、Compile linux

``make kernel_config``

``make kernel``



## 3、Compile rootfs

``make rootfs``



# System burning instructions

## 1、burning u-boot

+ burning file：  images/u-boot.hex
+ burning tool：pctool/FlyMcu.exe
+ burning cmd：none

![](https://github.com/johnnywei499/linux-for-mcu/blob/main/doc/u-boot%20burning.png)



## 2、burning kernel

+ burning file：images/xipImage
+ burning tool：SecureCRT
+ burning cmd：loadkernel_ymodem



**example**：

**first Accessing u-boot command line, Enter a command: loadkernel_ymodem**

You can check the instructions for using ymodem in SecureCRT

![](https://github.com/johnnywei499/linux-for-mcu/blob/main/doc/image%20burning0.png)

![](https://github.com/johnnywei499/linux-for-mcu/blob/main/doc/image%20burning1.png)

![](https://github.com/johnnywei499/linux-for-mcu/blob/main/doc/image%20burning2.png)



## 3、burning dtb

+ burning file：images/cortex_m4-one.dtb
+ burning tool：SecureCRT
+ burning cmd：loaddtb_ymodem

**example**：

Refer to burning the kernel



## 4、burning rootfs

+ burning file：images/romfs.bin
+ burning tool：SecureCRT
+ burning cmd：loadrootfs_ymodem

**example**：

Refer to burning the kernel



# Boot Messages

```
U-Boot 2010.06-svn199 (Apr 05 2023 - 07:09:25)

DRAM:  192 KiB
*** Warning - bad CRC, using default environment

In:    serial
Out:   serial
Err:   serial
Hit any key to stop autoboot:  0 
16384 KiB extern_flash at 0:1 is now current device
read: 100%
using fdt
[    0.000000] Built 1 zonelists in Zone order, mobility grouping off.  Total pages: 254
[    0.000000] Kernel command line: mem=1M@0x68000000 console=ttyAMA0,115200 root=/dev/mtdblock1 rootfstype=romfs mtdparts=cortex_m4_eflash:4K(dtb),256K(rootfs)
[    0.000000] PID hash table entries: 16 (order: -6, 64 bytes)
[    0.000000] Dentry cache hash table entries: 1024 (order: 0, 4096 bytes)
[    0.000000] Inode-cache hash table entries: 1024 (order: 0, 4096 bytes)
[    0.000000] Memory: 940K/1024K available (574K kernel code, 59K rwdata, 72K rodata, 38K init, 35K bss, 84K reserved)
[    0.000000] Virtual kernel memory layout:
[    0.000000]     vector  : 0x00000000 - 0x00001000   (   4 kB)
[    0.000000]     fixmap  : 0xfff00000 - 0xfffe0000   ( 896 kB)
[    0.000000]     vmalloc : 0x00000000 - 0xffffffff   (4095 MB)
[    0.000000]     lowmem  : 0x68000000 - 0x68100000   (   1 MB)
[    0.000000]       .text : 0x08020000 - 0x080c1b24   ( 647 kB)
[    0.000000]       .init : 0x20004000 - 0x20007000   (  12 kB)
[    0.000000]       .data : 0x20002000 - 0x20013f80   (  72 kB)
[    0.000000]        .bss : 0x20013f80 - 0x2001cc00   (  36 kB)
[    0.000000] NR_IRQS:16 nr_irqs:16 16
[    0.000000] sched_clock: 32 bits at 100 Hz, resolution 10000000ns, wraps every 4294967286ms
[    0.010000] Calibrating delay loop... 111.51 BogoMIPS (lpj=557568)
[    0.100000] pid_max: default: 4096 minimum: 301
[    0.100000] Mount-cache hash table entries: 512
[    0.110000] devtmpfs: initialized
[    0.150000] bio: create slab <bio-0> at 0
[    0.180000] ROMFS MTD (C) 2007 Red Hat, Inc.
[    0.180000] Block layer SCSI generic (bsg) driver version 0.4 loaded (major 254)
[    0.180000] io scheduler noop registered
[    0.190000] io scheduler deadline registered
[    0.190000] io scheduler cfq registered (default)
[    0.190000] 40020400.gpio probe
[    0.190000] 40021400.gpio probe
[    0.190000] 40004400.serial: ttyAMA0 at MMIO 0x40004400 (irq = 17, base_baud = 0) is a cortex_m4_usart
[    0.330000] console [ttyAMA0] enabled
[    0.340000] cortex_m4_spi_probe
[    0.340000] cortex_m4-spi 40013000.spi: master is unqueued, this is deprecated
[    0.350000] 2 cmdlinepart partitions found on MTD device cortex_m4_eflash
[    0.360000] Creating 2 MTD partitions on "cortex_m4_eflash":
[    0.370000] 0x000000000000-0x000000001000 : "dtb"
[    0.380000] 0x000000001000-0x000000041000 : "rootfs"
[    0.420000] VFS: Mounted root (romfs filesystem) readonly on device 31:1.
[    0.430000] devtmpfs: mounted
init started: BusyBox v1.10.0 (2023-04-05 07:01:17 PDT)
starting pid 16, tty '': '/etc/init.d/rcS'
Welcome to Linux
starting pid 19, tty '': '-/bin/sh'


BusyBox v1.10.0 (2023-04-05 07:01:17 PDT) built-in shell (msh)
Enter 'help' for a list of built-in commands.

# 
```
