#include <linux/kernel.h>
#include <asm/v7m.h>
#include <asm/mach/arch.h>
#include <asm/mach-types.h>
#include <linux/console.h>
#include <asm/io.h>
#include <linux/of_platform.h>
#include <linux/memblock.h>

static const char *const cortex_m4_compat[] __initconst = {
	"arm,cortex_m4",
	NULL
};

#ifndef CONFIG_SERIAL_CORTEX_M4_USART_CONSOLE
#define USART_SR 		0x00
#define USART_DR 		0x04 
#define USART_SR_TXE	(0x1UL << 7U)
#define USART_BASE		0x40004400

static void cortex_m4_console_putchar(int ch)
{
	unsigned char __iomem *membase = (unsigned char __iomem *)USART_BASE;
	while (!(readl_relaxed(membase + USART_SR) & USART_SR_TXE))
		cpu_relax();

	writel_relaxed(ch, membase + USART_DR);
}

static void cortex_m4_console_write(struct console *co, const char *s, unsigned int cnt)
{
	unsigned int i;

	for (i = 0; i < cnt; i++, s++) {
		if (*s == '\n')
			cortex_m4_console_putchar('\r');
		cortex_m4_console_putchar(*s);
	}
}

static int cortex_m4_console_setup(struct console *co, char *options)
{
	return 0;
}

static struct console cortex_m4_console = {
	.name		= "ttyAMA",
	.write		= cortex_m4_console_write,
	.setup		= cortex_m4_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
};
#endif

static void cortex_m4_init_machine(void)
{
	/* 0x20000000 ~ 0x20001000 reserves memory for dtb */
	//memblock_add(0x20001000, 0x1F000);
#ifndef CONFIG_SERIAL_CORTEX_M4_USART_CONSOLE
	register_console(&cortex_m4_console);
#endif
	of_platform_populate(NULL, of_default_bus_match_table, NULL, NULL);
}

DT_MACHINE_START(CORTEX_M4_DT, "cortex_m4 (Device Tree Support)")
	.dt_compat = cortex_m4_compat,
	.init_machine = cortex_m4_init_machine,
	.restart = armv7m_restart,
MACHINE_END
