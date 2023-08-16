/*
 * port.h
 *
 *  Created on: Aug 13, 2023
 *      Author: fert2
 */

#ifndef API_INC_PORT_H_
#define API_INC_PORT_H_

#include <stm32f4xx_ll_tim.h>
#include "stm32f4xx_hal.h"
#include <stdint.h>

/**
 * @brief Structure that defines the DHT configuration
 *
 * @param pin GPIO pin number
 * @param port GPIO port
 * @param EXTI_IRQn GPIO interrupt
 * @param htim Timer handle
 */
typedef struct
{
  uint16_t pin;                // GPIO pin number
  GPIO_TypeDef *port;          // GPIO port
  IRQn_Type EXTI_IRQn;        // GPIO interrupt
  TIM_HandleTypeDef *htim;     // Timer handle
} dhtConf_t;

/**
 * @brief Initializes the DHT pin
 *
 * @param GPIO_port GPIO port
 * @param GPIO_Pin GPIO pin number
 * @param PIN_EXTI_IRQn GPIO interrupt
 * @param TIMHandle Timer handle
 */
void Port_dhtPinInit(GPIO_TypeDef *GPIO_port, uint16_t GPIO_Pin,
                      IRQn_Type PIN_EXTI_IRQn, TIM_HandleTypeDef *TIMHandle);

/**
 * @brief Configures the pin as output
 */
void configPinAsOutput(void);

/**
 * @brief Configures the pin as input
 */
void configPinAsItInput(void);

/**
 * @brief Sets the pin to high
 */
void setPin(void);

/**
 * @brief Sets the pin to low
 */
void resetPin(void);

/**
 * @brief Gets the value of the timer
 *
 * @return Timer value
 */
uint32_t getTick(void);

/**
 * @brief Sets the value of the timer counter
 *
 * @param count Counter value
 */
void setTimerCounter(uint32_t count);

/**
 * @brief Gets the value of the timer counter
 *
 * @return Counter value
 */
uint32_t getTimerCouter(void);

#endif /* API_INC_PORT_H_ */