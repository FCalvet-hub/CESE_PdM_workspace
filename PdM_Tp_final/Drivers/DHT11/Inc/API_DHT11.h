/**
 * @file API_DHT11.h
 * @author Fernando Nicolas Calvet (fernando.n.calvet@gmail.com)
 * @brief Biblioteca para la lectura de datos del sensor DHT11.
 *
 * La biblioteca proporciona funciones para la inicialización, lectura de datos y
 * obtención de la temperatura y humedad del sensor DHT11.
 *
 * @version 0.1
 * @date 2023-08-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef API_INC_API_DHT11_H_
#define API_INC_API_DHT11_H_

#include <API_DHT11_port.h>

/**
 * @brief Structure to store the temperature of the DHT sensor.
 *
 * The structure contains two fields:
 * integers: The integer part of the temperature.
 * decimals: The decimal part of the temperature.
 */
typedef struct
{
	uint8_t integers;
	uint8_t decimals;
} dhtTemp_t;

/**
 * @brief Function that implements the DHT sensor FSM.
 *
 * The function is responsible for controlling the state of the DHT sensor and performing the necessary actions in each state.
 */
void dhtFSM_update(void);

/**
 * @brief Function to start communication with the DHT sensor.
 */
void dhtStartComm(void);

/**
 * @brief Function to initialize the DHT sensor.
 */
void dhtInit();

/**
 * @brief Function to get the temperature of the DHT sensor.
 *
 * @return dhtTemp_t Structure with the temperature data.
 */
dhtTemp_t dhtGetTemp(void);

/**
 * @brief Function to get the humidity of the DHT sensor.
 *
 * @return uint8_t Humidity of the DHT sensor.
 */
uint8_t dhtGetHum(void);

void dhtFallingEdgePinISRHandler(void);

#endif /* API_INC_API_DHT11_H_ */
