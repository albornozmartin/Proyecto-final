/* ************************************************************************** */
/** 
  @File Name
    puntuacion.c

@Summary
    Tarea que contabiliza la cantidad de puntos.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */


#include "puntuacion.h"

/* ************************************************************************** */
/* ************************************************************************** */

/** 
  @Function
    void contarPuntuacion(void *p_param) ;

  @Summary
    Cada vez que se ingresa a la tarea suma 1 a la puntuación.
 */

void contarPuntuacion(void *p_param) {

    while (1) { 
                puntuacion++;
                vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }



    /* *****************************************************************************
     End of File
     */
