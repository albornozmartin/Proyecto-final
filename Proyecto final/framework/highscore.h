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

#ifndef _HIGHSCORE_H    /* Guard against multiple inclusion */
#define _HIGHSCORE_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */


#include "enemigo.h"
#include "jugador.h"
#include "puntuacion.h"
#include "../mcc_generated_files/memory/flash.h"


#include "../mcc_generated_files/pin_manager.h"
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include"../freeRTOS/include/timers.h"
#include "../freeRTOS/include/semphr.h"  



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


    /* ************************************************************************** */
    /* ************************************************************************** */
    /* Section: Constants                                                         */
    /* ************************************************************************** */
    /* ************************************************************************** */

    /*  A brief description of a section can be given directly below the section
        banner.
     */

    /* ************************************************************************** */
    /** Descriptive Constant Name

      @Summary
        Brief one-line summary of the constant.
    
      @Description
        Full description, explaining the purpose and usage of the constant.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
      @Remarks
        Any additional remarks
     */
extern bool estaJugando;
extern int puntuacion;
extern bool contar;



    // *****************************************************************************
    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************
    // *****************************************************************************

   

    // *****************************************************************************


typedef enum {
    HIGHSCORE,
    JUEGO,
    FIN,
} MODO;


/** 
  @Function
void encenderPuntuacion(app_register_t unLed) 

  @Summary
     función utilizada para encender los Leds de la puntuación.
  
    @Parameters
    @app_regeister_t  unLed led a encender.
    
 */

void encenderPuntuacion(app_register_t unLed) ;

/** 
  @Function
void mostrarPuntuacion(int puntuacion)

  @Summary
 Según la puntuación, encenderá los leds 2, 3 y 5 de acuerdo al color correspondiente al número.

    @Parameters
    @int puntuacion 

 */

void mostrarPuntuacion(int puntuacion) ;


/** 
  @Function
void guardarEnMemoria()

  @Summary
 Guarda la puntuación en la memoria no volatil.

 */

void guardarEnMemoria();


/** 
  @Function
    void borrarMemoria() 

  @Summary
     Remplaza lo que haya en memoria por un 0;

 */

void borrarMemoria() ;


/** 
  @Function
uint32_t leerEnMemoria()

  @Summary
    Indica hacia donde mover el led del enemigo.


 */

uint32_t leerEnMemoria();




/** 
  @Function
void modoJuego(void *p_param) 

  @Summary
 Tarea inicial del juego.

  @Description
 Controla todos los modos del juego y permite guardar en memoria no volatil la puntuación máxima.
 */

void modoJuego (void *p_param);


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _HIGHSCORE_H */

/* *****************************************************************************
 End of File
 */
