#include <config.h>
#include <common.h>
#include "stm32f4xx_hal.h"

void reset_cpu(ulong ignored)
{
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}