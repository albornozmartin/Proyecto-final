/* ************************************************************************** */
/** 
  @File Name
 puntuacion.h

  @Summary
    Tarea que contabiliza la cantidad de puntos.

 */
/* ************************************************************************** */

#ifndef _PUNTUACION_H    /* Guard against multiple inclusion */
#define _PUNTUACION_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */


#include "highscore.h"
#include "enemigo.h"



/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/** 
  @Function
    void contarPuntuacion(void *p_param) ;

  @Summary
    Cada vez que se ingresa a la tarea suma 1 a la puntuación.
 */
    
void contarPuntuacion(void *p_param) ;
  


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PUNTUACION_H */

/* *****************************************************************************
 End of File
 */
