# Practica 2 - PdM

**Tabla de contenidos**
- [Practica 2 - PdM](#practica-2---pdm)
	- [Objetivo](#objetivo)
		- [Consigna](#consigna)
	- [Modificar tiempo de leds](#modificar-tiempo-de-leds)
	- [Funciones implementadas](#funciones-implementadas)
	- [Variables implementadas](#variables-implementadas)
		- [1. tick\_t](#1-tick_t)
		- [2. bool\_t](#2-bool_t)
		- [3. delay\_t](#3-delay_t)
		- [4. ledConf\_t](#4-ledconf_t)
	- [Plataforma de desarrollo](#plataforma-de-desarrollo)
	- [Autor](#autor)

## Plataforma de desarrollo
Compilado y probado para la placa de desarrollo **NUCLEO-F401RE**

*STM32F401RE Embedded Nucleo STM32F4 MCU 32-Bit ARM Cortex-M3 Evaluation Board*

## Objetivo
Implementar un módulo de software para trabajar con retardos no bloqueantes. 

### Consigna
Implementar un programa que utilice retardos no bloqueantes y  haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de la siguiente manera:
- LED1: 100 ms. 
- LED2: 500 ms.
- LED3: 1000 ms.

## Modificar tiempo de leds
Para modificar los tiempo de encendido de los led se deben modificar los #define ubicados en main.h

	#define LED1_DURATION 100
	#define LED2_DURATION 500
	#define LED3_DURATION 1000

## Funciones implementadas
	void delayInit( delay_t * delay, tick_t duration );
	bool_t delayRead( delay_t * delay );
	void delayWrite( delay_t * delay, tick_t duration );

## Variables implementadas
### 1. tick_t

	typedef uint32_t tick_t;

**Qué biblioteca se debe incluir para que esto compile?**
La libreria *<stdlib.h>*

### 2. bool_t

	typedef bool bool_t;

**Qué biblioteca se debe incluir para que esto compile?** La libreria *<stdbool.h>*
	
### 3. delay_t

	typedef struct{
	   tick_t startTime;
	   tick_t duration;
	   bool_t running;
	} delay_t;

Contiene todos los datos necesarios para el manejo del delay

### 4. ledConf_t

	typedef struct{
		uint16_t pin;
		GPIO_TypeDef *port;
		delay_t *delay;
	} ledConf_t;

Concatena todas las variables necesarias para el manejo de los led con sus respectivos puertos y tiempos de delay. Util para implementar loops y modificar variables en un solo lugar en el codigo

## Autor

Ing. Fernando Nicolas Calvet
@FCalvet
