/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <stdbool.h>
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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LD1_Pin GPIO_PIN_6
#define LD1_GPIO_Port GPIOA
#define LD3_Pin GPIO_PIN_7
#define LD3_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

#define LED1_DURATION 100
#define LED2_DURATION 500
#define LED3_DURATION 1000

typedef uint32_t tick_t; // stdint

typedef bool bool_t;	  // stdbool

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

typedef struct{
  uint16_t pin;
  GPIO_TypeDef *port;
  delay_t *delay;
} ledConf_t;

/**
 * @brief Delay struct inicialization
 *        Note: call it allways before any other ralated delay function
 * 
 * @param delay pointer to delay_t struct
 * @param duration delay duration in [ms]
 */
void delayInit( delay_t * delay, tick_t duration );

/**
 * @brief Read if configurated delay is completed
 * 
 * @param delay point to delay struct, 
 * @return bool_t true if completed, false if not
 */
bool_t delayRead( delay_t * delay );

/**
 * @brief Change existing delay
 * 
 * @param delay points to delay_t struct
 * @param duration delay duration in [ms]
 */
void delayWrite( delay_t * delay, tick_t duration );

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
