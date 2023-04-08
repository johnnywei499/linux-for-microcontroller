#include <common.h>
#include <command.h>
#include <asm/io.h>
#include "stm32f4xx_hal.h"
#include "cortex_m4/uart.h"

#define MAX_UART_SIZE 255
#define MAX_KERNEL_SIZE (896 * 1024)

DECLARE_GLOBAL_DATA_PTR;

extern UART_HandleTypeDef huart_data;

int uart_load_file(ulong load_addr)
{
	uint32_t i, j, checksum = 0;
	uint8_t rxbuf[MAX_UART_SIZE + 1] = {0};
	uint8_t ack[2] = {'O', 'K'};
	uint32_t offset = 0, len, filelen;
	
	//get file size
	if (HAL_OK != HAL_UART_Receive(&huart_data, rxbuf, 4, 10000)) {
		goto Timeout;
	}
	filelen = (rxbuf[3] << 24) | (rxbuf[2] << 16) | (rxbuf[1] << 8) | rxbuf[0];
	//ACK
	HAL_UART_Transmit(&huart_data, (uint8_t *)ack, 2, 100);
	
	while (1) {
		if (HAL_OK != HAL_UART_Receive(&huart_data, rxbuf, MAX_UART_SIZE + 1, 10000)) {
			goto Timeout;
		}
		len = rxbuf[0];
		if (len == 0) {
			HAL_UART_Transmit(&huart_data, (uint8_t *)ack, 2, 100);
			break;
		}
		// todo
		memcpy(load_addr + offset, (uint16_t *)(rxbuf + 1), len);
		offset += len;
		//ACK
		HAL_UART_Transmit(&huart_data, (uint8_t *)ack, 2, 100);

		if (len != MAX_UART_SIZE)
			break;

		printf("\33[2K\r");
		printf("read: %d%%", (offset * 100) / filelen);
	}
	printf("\33[2K\r");
	printf("read: %d%%", 100);
	printf("\n");
	printf("file size: %d\n", offset);

	if (offset > MAX_KERNEL_SIZE)
		goto SizeErr;

	for (i = 0; i < offset; i += MAX_UART_SIZE) {
		int length;
		if (offset - i < MAX_UART_SIZE)
			length = offset - i;
		else
			length = MAX_UART_SIZE;
		memcpy((uint16_t *)rxbuf, load_addr + i, MAX_UART_SIZE);
		for (j = 0; j < length; j++) {
			checksum += rxbuf[j];
		}
	}

	HAL_UART_Transmit(&huart_data, (uint8_t *)&checksum, 2, HAL_MAX_DELAY);
	return 0;
	
Timeout:
	printf("%s timeout...\n", __func__);
	return -1;
SizeErr:
	printf("%s too large...\n", __func__);
	return -1;
}

int do_load_file(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong load_addr = CONFIG_SYS_LOAD_ADDR;

	if (argc >= 2) {
		load_addr = simple_strtoul(argv[1], NULL, 16);
	}
	
	printf("load addr: 0x%x\r\n", load_addr);

	return uart_load_file(load_addr);
}

static struct tag *params;

static void setup_start_tag(bd_t *bd)
{
	params = (struct tag *) bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

static void setup_commandline_tag (bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

static void setup_end_tag (bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

int do_boot_xipkernel(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uint32_t value;
	bd_t *bd = gd->bd;
	int	machid;
	ulong kernel_addr = CONFIG_KERNEL_ADDR;
	int fdt = 1;
	char *commandline = getenv ("bootargs");
	
	if (argc >= 2) {
		if ((argv[1][0] == 'd')) {
			fdt = 1;
		} else {
			kernel_addr = simple_strtoul(argv[1], NULL, 16);
		}
	}

	run_command("sf probe 1", 0);
	run_command("sf read 0x20000000 0x00 0x1000", 0);
	run_command("fdt addr 0x20000000", 0);
	run_command("fdt c", 0);

	if (!fdt) {
		setup_start_tag(bd);
		setup_commandline_tag(bd, commandline);
		setup_end_tag(bd);
	} else {
		//printf("using fdt\n");
	}

	/* disable systick */
	value = readl(SysTick_BASE);
	value &= ~(0x01);
	writel(value, SysTick_BASE);
	
	machid = bd->bi_arch_number;
	void (*theKernel)(int zero, int arch, uint params);
	theKernel = (void (*)(int, int, uint))kernel_addr + 1;

	theKernel (0, machid, bd->bi_boot_params);
	
	return 0;
}

int do_load_dtb(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (uart_load_file(CONFIG_SYS_LOAD_ADDR) == 0) {
		run_command("sf probe 1", 0);
		run_command("sf write 0x68000000 0x00 0x1000", 0);
	}
	return 0;
}

int do_load_dtb_ymodem(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (run_command("loady", 0) == 0) {
		run_command("sf probe 1", 0);
		run_command("sf write 0x68000000 0x00 0x1000", 0);
	} else {
		printf("%s failed\n", __func__);
	}
	return 0;
}

int do_load_kernel(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (uart_load_file(CONFIG_SYS_LOAD_ADDR) == 0) {
		run_command("sf probe 0", 0);
		run_command("sf write 0x68000000 0x20000 0xe0000", 0);
	}
	return 0;
}

int do_load_kernel_ymodem(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (run_command("loady", 0) == 0) {
		run_command("sf probe 0", 0);
		run_command("sf write 0x68000000 0x20000 0xe0000", 0);
	} else {
		printf("%s failed\n", __func__);
	}
	return 0;
}

int do_load_rootfs(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (uart_load_file(CONFIG_SYS_LOAD_ADDR) == 0) {
		run_command("sf probe 1", 0);
		run_command("sf write 0x68000000 0x1000 0x40000", 0);
	}
	return 0;
}

int do_load_rootfs_ymodem(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	if (run_command("loady", 0) == 0) {
		run_command("sf probe 1", 0);
		run_command("sf write 0x68000000 0x1000 0x40000", 0);
	} else {
		printf("%s failed\n", __func__);
	}
	return 0;
}

U_BOOT_CMD(
	loadfile, 2, 1,	do_load_file,
	"cortex_m4 load file by usart3",
	"dummy"
);

U_BOOT_CMD(
	xipkernel, 2, 1, do_boot_xipkernel,
	"cortex_m4 boot xipkernel",
	"dummy"
);

U_BOOT_CMD(
	loaddtb, 2,	1, do_load_dtb,
	"cortex_m4 load dtb by usart3",
	"dummy"
);

U_BOOT_CMD(
	loaddtb_ymodem, 2,	1, do_load_dtb_ymodem,
	"cortex_m4 load dtb by ymodem",
	"dummy"
);

U_BOOT_CMD(
	loadkernel,	2, 1, do_load_kernel,
	"cortex_m4 load kernel by usart3",
	"dummy"
);

U_BOOT_CMD(
	loadkernel_ymodem,	2, 1, do_load_kernel_ymodem,
	"cortex_m4 load kernel by ymodem",
	"dummy"
);

U_BOOT_CMD(
	loadrootfs,	2, 1, do_load_rootfs,
	"cortex_m4 load rootfs by usart3",
	"dummy"
);

U_BOOT_CMD(
	loadrootfs_ymodem,	2, 1, do_load_rootfs_ymodem,
	"cortex_m4 load rootfs by ymodem",
	"dummy"
);
