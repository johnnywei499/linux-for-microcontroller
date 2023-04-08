#include <common.h>
#include <asm/io.h>
#include <asm/arch/platform.h>
#include "uart.h"

UART_HandleTypeDef huart;
UART_HandleTypeDef huart_data;

void UART_Init(void)
{
	huart.Instance = USART2;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		
	}

	huart_data.Instance = USART3;
	huart_data.Init.BaudRate = 2000000;
	huart_data.Init.WordLength = UART_WORDLENGTH_8B;
	huart_data.Init.StopBits = UART_STOPBITS_1;
	huart_data.Init.Parity = UART_PARITY_NONE;
	huart_data.Init.Mode = UART_MODE_TX_RX;
	huart_data.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart_data.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart_data) != HAL_OK)
	{
		
	}
}

/**
  * @brief UART MSP Initialization
  * This function configures the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	if (huart->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspInit 0 */

		/* USER CODE END USART1_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART1_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN USART1_MspInit 1 */

		/* USER CODE END USART1_MspInit 1 */
	}
	else if (huart->Instance == USART2)
	{
		/* USER CODE BEGIN USART2_MspInit 0 */

		/* USER CODE END USART2_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART2_CLK_ENABLE();

		__HAL_RCC_GPIOA_CLK_ENABLE();
		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN USART2_MspInit 1 */

		/* USER CODE END USART2_MspInit 1 */
	}
	else if (huart->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspInit 0 */

		/* USER CODE END USART3_MspInit 0 */
		/* Peripheral clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOB_CLK_ENABLE();
		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* USER CODE BEGIN USART3_MspInit 1 */

		/* USER CODE END USART3_MspInit 1 */
	}
}

/**
  * @brief UART MSP De-Initialization
  * This function freeze the hardware resources used in this example
  * @param huart: UART handle pointer
  * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
	if (huart->Instance == USART1)
	{
		/* USER CODE BEGIN USART1_MspDeInit 0 */

		/* USER CODE END USART1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART1_CLK_DISABLE();

		/**USART1 GPIO Configuration
		PA9     ------> USART1_TX
		PA10     ------> USART1_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

		/* USER CODE BEGIN USART1_MspDeInit 1 */

		/* USER CODE END USART1_MspDeInit 1 */
	}
	else if (huart->Instance == USART2)
	{
	/* USER CODE BEGIN USART2_MspDeInit 0 */

		/* USER CODE END USART2_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART2_CLK_DISABLE();

		/**USART2 GPIO Configuration
		PA2     ------> USART2_TX
		PA3     ------> USART2_RX
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

		/* USER CODE BEGIN USART2_MspDeInit 1 */

		/* USER CODE END USART2_MspDeInit 1 */
	}
	else if (huart->Instance == USART3)
	{
		/* USER CODE BEGIN USART3_MspDeInit 0 */

		/* USER CODE END USART3_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_USART3_CLK_DISABLE();

		/**USART3 GPIO Configuration
		PB10     ------> USART3_TX
		PB11     ------> USART3_RX
		*/
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

		/* USER CODE BEGIN USART3_MspDeInit 1 */

		/* USER CODE END USART3_MspDeInit 1 */
	}
}

/* Indicates the serial port baud rate setting function pointer */
void serial_setbrg(void)
{
	
}

/*
 * it is the responsiblity of the board code to setup the proper pin
 * muxing for the selected UART
 */
/* Pointer to serial port initialization function */
int serial_init(void)
{
	serial_setbrg();

	return 0;
}

/* Indicates the function pointer to obtain a character from the serial port */
int serial_getc(void)
{
	int c;
	HAL_UART_Receive(&huart, &c, 1, HAL_MAX_DELAY);
	return c;
}

/* Function pointer indicating that the serial port sends one character */
void serial_putc(const char c)
{
	HAL_UART_Transmit(&huart, (uint8_t *)&c, 1, HAL_MAX_DELAY);
	
	/* If \n, also do \r */
	if (c == '\n')
		serial_putc('\r');
}

/* Function pointer indicating whether the serial port receives data */
int serial_tstc(void)
{
	return __HAL_UART_GET_FLAG(&huart, UART_FLAG_RXNE);
}

/* Function pointer representing the string sent by the serial port */
void serial_puts(const char *s)
{
	while (*s)
		serial_putc (*s++);
}
