/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f0xx_hal.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_cortex.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_utils.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_dma.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VIN_FB_Pin LL_GPIO_PIN_0
#define VIN_FB_GPIO_Port GPIOA
#define VOUT_FB_Pin LL_GPIO_PIN_1
#define VOUT_FB_GPIO_Port GPIOA
#define IOUT_FB_Pin LL_GPIO_PIN_2
#define IOUT_FB_GPIO_Port GPIOA
#define TEMP_Pin LL_GPIO_PIN_3
#define TEMP_GPIO_Port GPIOA
#define VREF_Pin LL_GPIO_PIN_4
#define VREF_GPIO_Port GPIOA
#define IREF_Pin LL_GPIO_PIN_5
#define IREF_GPIO_Port GPIOA
#define BTN_ON_Pin LL_GPIO_PIN_6
#define BTN_ON_GPIO_Port GPIOA
#define BTN_ON_EXTI_IRQn EXTI4_15_IRQn
#define EC11_BTN_Pin LL_GPIO_PIN_7
#define EC11_BTN_GPIO_Port GPIOA
#define EC11_BTN_EXTI_IRQn EXTI4_15_IRQn
#define EC11_A_Pin LL_GPIO_PIN_0
#define EC11_A_GPIO_Port GPIOB
#define EC11_A_EXTI_IRQn EXTI0_1_IRQn
#define EC11_B_Pin LL_GPIO_PIN_1
#define EC11_B_GPIO_Port GPIOB
#define LCD_MOSI_Pin LL_GPIO_PIN_2
#define LCD_MOSI_GPIO_Port GPIOB
#define LCD_SCK_Pin LL_GPIO_PIN_10
#define LCD_SCK_GPIO_Port GPIOB
#define LCD_DC_Pin LL_GPIO_PIN_11
#define LCD_DC_GPIO_Port GPIOB
#define LCD_RST_Pin LL_GPIO_PIN_12
#define LCD_RST_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
