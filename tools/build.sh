#/!bin/bash

function boot_config()
{
	cd u-boot-2010.06 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- cortex_m4_config && cd -
}

function boot()
{
	cd u-boot-2010.06 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- && cd -
}

function boot_clean()
{
	cd u-boot-2010.06 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- clean && cd -
}

function kernel_config()
{
	cd linux-3.12.74 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- cortex_m4_defconfig && cd -
}

function kernel()
{
	cd linux-3.12.74 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- && cd -
	cd linux-3.12.74 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- cortex_m4-one.dtb && cd -
}

function kernel_clean()
{
	cd linux-3.12.74 && make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- clean && cd -
}

function rootfs()
{
	cd busybox-1.10.0/
	rm _install/ -rf
	make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- CFLAGS="-march=armv7-m -mthumb -fPIC -Wl,-elf2flt" SKIP_STRIP=y
	make ARCH=arm CROSS_COMPILE=arm-m4-linux-uclibceabi- CFLAGS="-march=armv7-m -mthumb -fPIC -Wl,-elf2flt" SKIP_STRIP=y install
	cd -
	rm rootfs -rf
	mkdir -p rootfs
	cp rfs/* rootfs/ -rf
	cp busybox-1.10.0/_install/* rootfs/ -rf

	cd usr/
	make 
	cd -
	
	cp usr/demo rootfs/bin/ -rf
	genromfs -d rootfs/ -f romfs.bin
	rm rootfs -rf
}

function usage()
{
	echo "help"
}

main()
{
	STEPS=""
	while getopts s: arg
    do case $arg in
		s)  STEPS=$OPTARG;;
      	h)  usage
          	exit 0;;
      	*)  usage
          	exit 1;;
    esac
	done

	for step in `echo "$STEPS" | sed 's/,/\n/g'`
    do
    	$step
    done
}

main "$@"
