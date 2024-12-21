/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CLEAR_Pin GPIO_PIN_0
#define CLEAR_GPIO_Port GPIOA
#define A_HT_Pin GPIO_PIN_1
#define A_HT_GPIO_Port GPIOA
#define CLK_A_HT_Pin GPIO_PIN_2
#define CLK_A_HT_GPIO_Port GPIOA
#define EN_HT_Pin GPIO_PIN_3
#define EN_HT_GPIO_Port GPIOA
#define A_HO_Pin GPIO_PIN_4
#define A_HO_GPIO_Port GPIOA
#define CLK_A_HO_Pin GPIO_PIN_5
#define CLK_A_HO_GPIO_Port GPIOA
#define A_MT_Pin GPIO_PIN_6
#define A_MT_GPIO_Port GPIOA
#define CLK_A_MT_Pin GPIO_PIN_7
#define CLK_A_MT_GPIO_Port GPIOA
#define BTN_UP_Pin GPIO_PIN_0
#define BTN_UP_GPIO_Port GPIOB
#define BTN_DOWN_Pin GPIO_PIN_1
#define BTN_DOWN_GPIO_Port GPIOB
#define BTN_LEFT_Pin GPIO_PIN_2
#define BTN_LEFT_GPIO_Port GPIOB
#define EN_MO_Pin GPIO_PIN_12
#define EN_MO_GPIO_Port GPIOB
#define EN_ST_Pin GPIO_PIN_13
#define EN_ST_GPIO_Port GPIOB
#define EN_SO_Pin GPIO_PIN_14
#define EN_SO_GPIO_Port GPIOB
#define A_MO_Pin GPIO_PIN_8
#define A_MO_GPIO_Port GPIOA
#define CLK_A_MO_Pin GPIO_PIN_9
#define CLK_A_MO_GPIO_Port GPIOA
#define A_ST_Pin GPIO_PIN_10
#define A_ST_GPIO_Port GPIOA
#define CLK_A_ST_Pin GPIO_PIN_11
#define CLK_A_ST_GPIO_Port GPIOA
#define A_SO_Pin GPIO_PIN_12
#define A_SO_GPIO_Port GPIOA
#define CLK_A_SO_Pin GPIO_PIN_15
#define CLK_A_SO_GPIO_Port GPIOA
#define BTN_RIGHT_Pin GPIO_PIN_3
#define BTN_RIGHT_GPIO_Port GPIOB
#define EN_HO_Pin GPIO_PIN_4
#define EN_HO_GPIO_Port GPIOB
#define EN_MT_Pin GPIO_PIN_5
#define EN_MT_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
