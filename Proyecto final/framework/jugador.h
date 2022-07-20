/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#ifndef _JUGADOR_H    /* Guard against multiple inclusion */
#define _JUGADOR_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files   
 *                                                  */
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include"../freeRTOS/include/timers.h"
#include "../freeRTOS/include/semphr.h"  
#include "../mcc_generated_files/pin_manager.h"
#include "Accelerometer/Accelerometer.h"
#include "../platform/WS2812.h"
#include <math.h>


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Global Data                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

  /** ledActualJugador

  @Summary
    Entero utilizado para guardar la posición actual del jugador.
    
  @Description
    Entero que se comparte entre tareas para guardar la posición del led blanco, esto permite que sea alcanzado por el led rojo.
   
  @Remarks
    Protegido por un semáforo.
 */
  
    extern  int ledActualJugador;
    
    
    /** arrayLEDS

  @Summary
    Arreglo con los 8 Leds de la placa.
    
  @Description
 Este arreglo almacena los datos de los leds para encender en la placa, es un recurso compartido entre la tarea del jugador
  y la tarea del enemigo.
   
  @Remarks
    Protegido por un semáforo. 
 */
    
    extern   ws2812_t arrayLEDS[8];
    
    
    /** semaforo

  @Summary
    Handler del semáforo.
    
  @Description
    Se utiliza este semáforo para controlar que tarea tiene acceso a los recursos compartidos.
   
 */
    
    extern SemaphoreHandle_t semaforo;
    

    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************


    // *****************************************************************************

    /** Descriptive Data Type Name */


 typedef struct {
   /* Estructura para controlar los datos de los LED */
int led;
/* Entero que corresponde al n?mero del LED, entre 0 y 7. */
uint8_t color;     
/* Entero que corresponde al n?mero del color del LED, 0-Blanco 1-Rojo 2-Azul 3-Verde 4-Negro. */
uint32_t time;
/* Entero que corresponde a la fecha en que fue modificado. */
bool ledModificado;
/* Booleano que indica si el LED fue modificado o no.*/
  uint32_t tiempoEncendido; 
  /* Indica el tiempo que debe pasar antes de que el LED se encienda..*/
} app_register_t;


    // *****************************************************************************
    // *****************************************************************************
    // Section: Functions
    // *****************************************************************************
    // *****************************************************************************

    
/** 
  @Function
 void encenderLED(app_register_t unLed);

  @Summary
    Enciende los leds del array.

  @Description
 Setea el color y llama a la función de los LEDS para encenderlos.

  @Precondition
 Debe estar creado el arrrayLEDS.

  @Parameters
    @param unLed, tipo app_register_t.
 */

void encenderLED(app_register_t unLed);


/** 
  @Function
 apagarTodos();

  @Summary
 Apaga todos los LEDs de la placa.
 */

void apagarTodos();

/** 
  @Function
 void jugador(void *p_param);

  @Summary
    Función principal para controlar la posición del jugador.

  @Description
    Es una tarea que cada 1 ms, actualiza la posición del jugador en base al movimiento realizado en la placa, capturado por 
    el acelerómetro
 */


/** 
  @Function
 void jugador(void *p_param);

  @Summary
    Función principal para controlar la posición del jugador.

  @Description
    Es una tarea que cada 1 ms, actualiza la posición del jugador en base al movimiento realizado en la placa, capturado por 
    el acelerómetro
 */

void jugador( void *p_param );
   
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _JUGADOR_H */

/* *****************************************************************************
 End of File
 */
