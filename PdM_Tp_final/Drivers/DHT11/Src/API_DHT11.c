/*
 * API_DHT11.c
 *
 *  Created on: 31 jul. 2023
 *      Author: fcalvet
 */

#include <API_DHT11_port.h>
#include "API_DHT11.h"
#include <stdbool.h>
#include <stdio.h>

#define DELAY_START_COMM 18	  // uS
#define TIMEOUT_RX_DATA 20	  // uS
#define START_MCU_TIME 18	  // uS
#define DHT_TIME_THRESHOLD 85 // uS
#define DHT_DATA_BIT_LEN 40	  // uS

typedef union
{
	/* DHT sensor data structure */
	struct
	{
		uint8_t checksum; // Checksum
		uint8_t t_dec;	  // Temperature decimal
		uint8_t t_int;	  // Temperature integer
		uint8_t h_dec;	  // Humidity decimal
		uint8_t h_int;	  // Humidity integer
	};
	/* Representation of the data as a 64-bit number */
	uint64_t raw;
} dhtDataFormat_t;

typedef enum
{
	/* DHT FSM states */
	INIT,			 // Initialization
	IDLE,			 // Idle
	STARTCOMM_INIT,	 // Communication initialization
	STARTCOMM_DELAY, // Communication delay
	STARTCOMM_END,	 // Communication end
	RX_DATA,		 // Data reception
	EVAL_DATA		 // Data evaluation
} FSM_states;

static uint8_t state;
static dhtDataFormat_t dhtStoredData;

volatile dhtDataFormat_t dhtBinData;
volatile uint8_t bitCounter = 0;

void dhtInit()
{
	/* Set the pin as output */
	configPinAsOutput();

	/* First FSM state */
	state = INIT;
}

void dhtStartComm(void)
{
	// If the FSM is already running, do not reinitialize
	if (state == IDLE)
	{
		state = STARTCOMM_INIT;
	}
}

/**
 * @brief Function to check if the checksum of the DHT sensor data is correct.
 *
 * @param data DHT sensor data.
 *
 * @return true if the checksum is correct, false otherwise.
 */
bool isDhtChecksumOk()
{
	uint8_t chsum = 0; // Checksum

	// Calculate the checksum of the data
	chsum += dhtBinData.t_int;
	chsum += dhtBinData.t_dec;
	chsum += dhtBinData.h_int;
	chsum += dhtBinData.h_dec;

	// Compare the calculated checksum with the sensor's checksum
	return (dhtBinData.checksum == chsum);
}

void storeData()
{
	dhtStoredData.t_int = dhtBinData.t_int;
	dhtStoredData.t_dec = dhtBinData.t_dec;
	dhtStoredData.h_int = dhtBinData.h_int;
}

/**
 * @brief Function that implements the DHT sensor FSM.
 *
 * The function is responsible for controlling the state of the DHT sensor and performing the necessary actions in each state.
 *
 * @param void
 *
 * @return void
 */
void dhtFSM_update(void)
{
	static uint32_t last_time, countdown;

	switch (state)
	{
	case INIT:
		// Set the GPIO pin as output and set it high
		configPinAsOutput();
		setPin();
		state = IDLE;
		break;

	case IDLE:
		// Waiting...
		break;

	case STARTCOMM_INIT:
		state = STARTCOMM_DELAY;
		// Reset the counter
		bitCounter = 0;
		// Set the GPIO pin low
		resetPin();
		// Store the current time
		last_time = getTick();
		break;

	case STARTCOMM_DELAY:
		// Calculate the elapsed time since the last state
		countdown = getTick() - last_time;
		// If the elapsed time is greater than the communication start delay,
		// change to the STARTCOMM_END state
		if (countdown >= DELAY_START_COMM)
		{
			setPin();
			dhtBinData.raw = 0;
			configPinAsItInput();
			// Reset the timer counter
			setTimerCounter(0);
			state = STARTCOMM_END;
		}
		break;

	case STARTCOMM_END:
		// Store the current time
		last_time = getTick();

		state = RX_DATA;
		break;

	case RX_DATA:
		// Calculate the elapsed time since the last state
		countdown = getTick() - last_time;

		// If we have received all the data or the timeout has expired
		if (((countdown) >= TIMEOUT_RX_DATA) || (bitCounter >= DHT_DATA_BIT_LEN))
		{
			state = EVAL_DATA;
		}
		break;

	case EVAL_DATA:
		// If the binary data checksum is correct,
		// store the data
		if (isDhtChecksumOk())
		{
			storeData();
		}
		else
		{
			// ERROR
		}
		storeData();

		state = INIT;
		break;

	default:
		state = INIT;
		break;
	}
}

dhtTemp_t dhtGetTemp(void)
{
	dhtTemp_t temp;

	temp.integers = dhtStoredData.t_int;
	temp.decimals = dhtStoredData.t_dec;

	return temp;
}

uint8_t dhtGetHum(void)
{
	return dhtStoredData.h_int;
}

volatile uint32_t aux = 0;
/*
 * Callback function that is invoked when an interrupt occurs on the GPIO
 *
 * Parameters:
 *   GPIO_Pin: GPIO pin that generated the interrupt.
 */
void dhtFallingEdgePinISRHandler(void)
{	
	dhtBinData.raw <<= 1;
	aux = getTimerCouter();
	// If the timer value is greater than the DHT_TIME_THRESHOLD, the most significant bit of the binary data is set to 1,
	// otherwise it is set to 0
	dhtBinData.raw |= (getTimerCouter() > DHT_TIME_THRESHOLD) ? 1 : 0;
	
	bitCounter++;	
	setTimerCounter(0);
}