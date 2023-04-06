# linux-for-mcu 
This is a linux-3.12.74 project that can run on stm32f407

The source code will be uploaded at a later time

For more information, please contact email johnnywei499@gmail.com

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
