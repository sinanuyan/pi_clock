/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "clock_thread.h"
#include "button_thread.h"
#include "7_segment.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

	HAL_GPIO_WritePin(EN_HO_GPIO_Port, EN_HO_Pin, 0);
	HAL_GPIO_WritePin(EN_HT_GPIO_Port, EN_HT_Pin, 0);
	HAL_GPIO_WritePin(EN_MO_GPIO_Port, EN_MO_Pin, 0);
	HAL_GPIO_WritePin(EN_MT_GPIO_Port, EN_MT_Pin, 0);
	HAL_GPIO_WritePin(EN_SO_GPIO_Port, EN_SO_Pin, 0);
	HAL_GPIO_WritePin(EN_ST_GPIO_Port, EN_ST_Pin, 0);

	HAL_GPIO_WritePin(A_HT_GPIO_Port, A_HT_Pin, 1);
	HAL_GPIO_WritePin(CLEAR_GPIO_Port, CLEAR_Pin, 1);

	uint8_t data[6] = {
	SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK, SEG_BLANK };
	//segment_write(data, 0);

	RTC_TimeTypeDef sTimeStamp;
	RTC_DateTypeDef sTimeStampDate;

	uint8_t bcd;
	uint8_t old_sec = 15;

	uint8_t sht_addr = 0x88;

	uint8_t sht_tx[2] = { 0x20, 0x32 };
	uint8_t sht_rx[6];
	HAL_StatusTypeDef result;

	result = HAL_I2C_Master_Transmit(&hi2c1, sht_addr, sht_tx, 2, 10);

	result = HAL_I2C_Master_Receive(&hi2c1, sht_addr, sht_rx, 3, 10);

	uint8_t tx_data[100];

	uint16_t st = 0;
	uint32_t temp_seg = 0;
	st = sht_rx[0] << 8;
	st = st | sht_rx[1];

	float temperature = -45 + 175 * ((float) st / 65535);
	uint8_t hour_ten_value = 0;
	uint8_t hour_one_value = 0;
	uint8_t minute_ten_value = 0;
	uint8_t minute_one_value = 0;
	uint8_t second_ten_value = 0;
	uint8_t second_one_value = 0;

	data[0] = SEG_A;
	data[1] = SEG_A;
	data[2] = SEG_A;
	data[3] = SEG_A;
	data[4] = SEG_A;
	data[5] = SEG_A;

	seven_segment hour_ten;
	seven_segment hour_one;
	seven_segment minute_ten;
	seven_segment minute_one;
	seven_segment second_ten;
	seven_segment second_one;

	display disp;

	hour_ten.a_port = A_HT_GPIO_Port;
	hour_ten.a_pin = A_HT_Pin;
	hour_ten.clock_port = CLK_A_HT_GPIO_Port;
	hour_ten.clock_pin = CLK_A_HT_Pin;
	hour_ten.enable_port = EN_HT_GPIO_Port;
	hour_ten.enable_pin = EN_HT_Pin;
	hour_ten.enable_segment = 1;

	hour_one.a_port = A_HO_GPIO_Port;
	hour_one.a_pin = A_HO_Pin;
	hour_one.clock_port = CLK_A_HO_GPIO_Port;
	hour_one.clock_pin = CLK_A_HO_Pin;
	hour_one.enable_port = EN_HO_GPIO_Port;
	hour_one.enable_pin = EN_HO_Pin;
	hour_one.enable_segment = 1;

	minute_ten.a_port = A_MT_GPIO_Port;
	minute_ten.a_pin = A_MT_Pin;
	minute_ten.clock_port = CLK_A_MT_GPIO_Port;
	minute_ten.clock_pin = CLK_A_MT_Pin;
	minute_ten.enable_port = EN_MT_GPIO_Port;
	minute_ten.enable_pin = EN_MT_Pin;
	minute_ten.enable_segment = 1;

	minute_one.a_port = A_MO_GPIO_Port;
	minute_one.a_pin = A_MO_Pin;
	minute_one.clock_port = CLK_A_MO_GPIO_Port;
	minute_one.clock_pin = CLK_A_MO_Pin;
	minute_one.enable_port = EN_MO_GPIO_Port;
	minute_one.enable_pin = EN_MO_Pin;
	minute_one.enable_segment = 1;

	second_ten.a_port = A_ST_GPIO_Port;
	second_ten.a_pin = A_ST_Pin;
	second_ten.clock_port = CLK_A_ST_GPIO_Port;
	second_ten.clock_pin = CLK_A_ST_Pin;
	second_ten.enable_port = EN_ST_GPIO_Port;
	second_ten.enable_pin = EN_ST_Pin;
	second_ten.enable_segment = 1;

	second_one.a_port = A_SO_GPIO_Port;
	second_one.a_pin = A_SO_Pin;
	second_one.clock_port = CLK_A_SO_GPIO_Port;
	second_one.clock_pin = CLK_A_SO_Pin;
	second_one.enable_port = EN_SO_GPIO_Port;
	second_one.enable_pin = EN_SO_Pin;
	second_one.enable_segment = 1;

	hour_ten.data = 0;
	hour_ten.data_old = 255;
	hour_one.data = 0;
	hour_one.data_old = 255;
	minute_ten.data = 0;
	minute_ten.data_old = 255;
	minute_one.data = 0;
	minute_one.data_old = 255;
	second_ten.data = 0;
	second_ten.data_old = 255;
	second_one.data = 0;
	second_one.data_old = 255;

	disp.hour_ten = &hour_ten;
	disp.hour_one = &hour_one;
	disp.minute_ten = &minute_ten;
	disp.minute_one = &minute_one;
	disp.second_ten = &second_ten;
	disp.second_one = &second_one;

	disp.data = 0;
	display_write(&disp);


	//HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		disp.data++;
		display_write(&disp);
		HAL_Delay(1);

	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 31;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 499;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, CLEAR_Pin|A_HT_Pin|CLK_A_HT_Pin|EN_HT_Pin
                          |A_HO_Pin|CLK_A_HO_Pin|A_MT_Pin|CLK_A_MT_Pin
                          |A_MO_Pin|CLK_A_MO_Pin|A_ST_Pin|CLK_A_ST_Pin
                          |A_SO_Pin|CLK_A_SO_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11|EN_MO_Pin|EN_ST_Pin|EN_SO_Pin
                          |EN_HO_Pin|EN_MT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : CLEAR_Pin A_HT_Pin CLK_A_HT_Pin A_HO_Pin
                           CLK_A_HO_Pin A_MT_Pin CLK_A_MT_Pin A_MO_Pin
                           CLK_A_MO_Pin A_ST_Pin CLK_A_ST_Pin A_SO_Pin
                           CLK_A_SO_Pin */
  GPIO_InitStruct.Pin = CLEAR_Pin|A_HT_Pin|CLK_A_HT_Pin|A_HO_Pin
                          |CLK_A_HO_Pin|A_MT_Pin|CLK_A_MT_Pin|A_MO_Pin
                          |CLK_A_MO_Pin|A_ST_Pin|CLK_A_ST_Pin|A_SO_Pin
                          |CLK_A_SO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : EN_HT_Pin */
  GPIO_InitStruct.Pin = EN_HT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(EN_HT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BTN_UP_Pin BTN_DOWN_Pin BTN_LEFT_Pin BTN_RIGHT_Pin */
  GPIO_InitStruct.Pin = BTN_UP_Pin|BTN_DOWN_Pin|BTN_LEFT_Pin|BTN_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_MO_Pin EN_ST_Pin EN_SO_Pin EN_HO_Pin
                           EN_MT_Pin */
  GPIO_InitStruct.Pin = EN_MO_Pin|EN_ST_Pin|EN_SO_Pin|EN_HO_Pin
                          |EN_MT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
