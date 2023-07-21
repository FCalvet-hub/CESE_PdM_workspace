# Practica 4 - PdM

**Tabla de contenidos**
- [Practica 4 - PdM](#practica-4---pdm)
  - [Plataforma de desarrollo](#plataforma-de-desarrollo)
  - [Objetivo:](#objetivo)
  - [Ubicacion y archivos de los drivers](#ubicacion-y-archivos-de-los-drivers)
- [Uso de Debounce driver](#uso-de-debounce-driver)
  - [inicializacion](#inicializacion)
- [Detalles del funcionamiento del Debounce driver](#detalles-del-funcionamiento-del-debounce-driver)
  - [Autor](#autor)

## Plataforma de desarrollo
![alt text](401RE.webp "Placa")

Compilado y probado para la placa de desarrollo **NUCLEO-F401RE**

*STM32F401RE Embedded Nucleo STM32F4 MCU 32-Bit ARM Cortex-M3 Evaluation Board*

**NOTA:** Para esta practica, al poseer la placa un solo LED, se utilizaron las salidas **GPIO_PIN_7** y **GPIO_PIN_6** para el manejo de los 2 led restantes.

## Objetivo:
Implementar un MEF para trabajar con anti-rebotes por software. 

## Ubicacion y archivos de los drivers
```bash
├───Core
│   ├───Inc
│   ├───Src
│   └───Startup
└───Drivers
    ├───API
    │   ├───Inc     <--- API_debounce.h
    │   └───Scr     <--- API_debounce.c
    ├───CMSIS
    └───STM32F4xx_HAL_Driver
```
# Uso de Debounce driver

El driver consta principalmente de 2 funciones. Una de inicializacion y una de funcionamiento continuo.

## inicializacion

- Primero se deben declarar las funciones que se desean que se ejecuten en caso de apretar y soltar un boton.
Ejemplo:
```C
void button1Pressed(void){
	/*ACCIONES A REALIZAR CUANDO EL BOTON SE PRESIONA*/
}

void button1Released(void){
	/*ACCIONES A REALIZAR CUANDO EL BOTON SE LIBERA*/
}
```
- Se debe declarar una variable del tipo `debounce_t` e inicializarla con el **pin** usado como boton y las funcoines a ejecutarse en caso del que boton se presione o se libere.
Ejemplo:

```C
debounce_t button1 = {
  .port = B1_GPIO_Port,
  .pin = B1_Pin,
  .pressed = button1Pressed,
  .released = button1Released
};
```

- Una vez realizada esta inicializacion de la estructura, se debe llamar a la funcion `debounceFSM_init()` pasando como parametro la estructura `debounce_t` inicializada anteriormente.

Ejemplo:

```C
debounceFSM_init(&button1);
```

-Realizado esto, solo resta por poner en el **main loop** la funcion `debounceFSM_update()` para que se evalue constantemente si el boton fue presionado, pasando como parametro la estructura `debounce_t`.

Ejemplo:

```C
  while (1)
  {
	  debounceFSM_update(&button1);
  }
```
> Planteado el driver de esta manera, permite que se pueda declarar por ejemplo un array de botones y evaluarlos en un for loop.

# Detalles del funcionamiento del Debounce driver

> 
Estructura principal del driver:
```C
typedef struct {
    GPIO_TypeDef *port;      	/*!< Button pin port */
    uint16_t pin;           	/*!< Button pin */
    delay_t delay;          	/*!< Debounce delay */
    uint8_t state;          	/*!< Button state */
    void (*released)(void); 	/*!< Callback to function when button is released */
    void (*pressed)(void);  	/*!< Callback to function when button is pressed */
} debounce_t;
```
>Notar que entre los miembros de la estructura se encuentra `delay_t` para el manejo de los tiempos de debounce. Ver [Practica 3](../PdM_Practica_3/).

La funcion `debounceFSM_update()` implementa una maquina de estados segun el siguiente diagrama:
![alt text](FSM_diagram.png "Diagrama")

## Autor

Ing. Fernando Nicolas Calvet

@FCalvet