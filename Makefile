SCRIPTPATH 	= ./tools/build.sh
OPT 		= -s

boot_config:
	$(SCRIPTPATH) $(OPT) $@
boot:
	$(SCRIPTPATH) $(OPT) $@

kernel_config:
	$(SCRIPTPATH) $(OPT) $@
kernel:
	$(SCRIPTPATH) $(OPT) $@

rootfs:
	$(SCRIPTPATH) $(OPT) $@