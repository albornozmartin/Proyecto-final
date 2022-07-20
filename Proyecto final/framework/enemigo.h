/* ************************************************************************** */
/** 
  @File Name
    enemigo.h

@Summary
    Tarea que controla la posicion del led rojo.

  @Description
    En base a los recursos compartidos, controla la posicion del enemigo y las situaciones en las que se pierde el juego.
    A su vez, aumenta gradualmente la dificultad del juego a medida que pasa el tiempo.
 */
/* ************************************************************************** */

#ifndef _ENEMIGO_H    /* Guard against multiple inclusion */
#define _ENEMIGO_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */

#include <math.h>
#include <stdbool.h>


#include "jugador.h"
#include "highscore.h"
#include "puntuacion.h"
#include "../freeRTOS/include/FreeRTOS.h"
#include "../freeRTOS/include/task.h"
#include"../freeRTOS/include/timers.h"
#include "../freeRTOS/include/semphr.h"  


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

    
    /** 
  @Function
 void aumentarDificultad();

  @Summary
    Aumenta la dificultad superada cierta puntuación.
 */

    void aumentarDificultad();
  
    
    /** 
  @Function
int proximoMovimiento2(int ledJugador, int ledEnemigo)

  @Summary
    Indica hacia donde mover el led del enemigo.

  @Description
    En base a las posiciones de ambos led, calcula hacia donde debe ser el movimiento para alcanzar con la menor cantidad 
    de pasos posibles al led blanco.
  
    @Parameters
    @int ledJugador refiere al led de la posición del jugador.
    
    @int ledEnemigo refiere al led de la posición del enemigo.
 */
    
    int proximoMovimiento2(int ledJugador, int ledEnemigo);
    
    
    /** 
  @Function
    int spawn(int posicionJugador)

  @Summary
    Indica donde debe aparecer el enemigo.

  @Description
    En base a las posiciones del led blanco, indica donde debe aparecer el led enemigo.
  
    @Parameters
    @int posicionJugador refiere al led de la posición del jugador.
 */
    
    int spawn(int posicionJugador);
    
    
    /** 
  @Function
    void enemigo(void *p_param)

  @Summary
    Tarea principal que controla la posicion del enemigo y las condiciones para perder.

  @Description
     Tarea que controla si se perdió el juego, en base a los recursos compartidos con la tarea de la posición del jugador.
     Si la posicion del enemigo es igual a la del jugador entonces se termina el juego.
  
 */
    
    void enemigo(void *p_param);

    

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _ENEMIGO_H */

/* *****************************************************************************
 End of File
 */
