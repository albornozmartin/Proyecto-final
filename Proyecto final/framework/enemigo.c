/* ************************************************************************** */
/** 

  @File Name
    enemigo.c

  @Summary
    Tarea que controla la posicion del led rojo.

  @Description
    En base a los recursos compartidos, controla la posicion del enemigo y las situaciones en las que se pierde el juego.
    A su vez, aumenta gradualmente la dificultad del juego a medida que pasa el tiempo.
 */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include "enemigo.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
/*
@Summary
    Entero referido al tiempo de acceso a la tarea.
    
  @Description
    Entero que refeire al tiempo de acceso a la tarea, disminuye con el tiempo, haciendo que se acceda más seguido a la tarea 
    y por lo tanto, agregando dificultad al juego.
  
 */

int tiempoDificultad;


/* ************************************************************************** */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/** 
  @Function
 void aumentarDificultad();

  @Summary
    Aumenta la dificultad superada cierta puntuación.
 */

void aumentarDificultad() {
    if (puntuacion == 0) {
        tiempoDificultad = 1000;
    } else if (puntuacion == 10) {
        tiempoDificultad = 900;
    } else if (puntuacion == 20) {
        tiempoDificultad = 800;
    } else if (puntuacion == 30) {
        tiempoDificultad = 700;
    } else if (puntuacion == 40) {
        tiempoDificultad = 600;
    } else if (puntuacion == 50) {
        tiempoDificultad = 500;
    } else if (puntuacion == 60) {
        tiempoDificultad = 400;
    }
}
  

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


int proximoMovimiento2(int ledJugador, int ledEnemigo) {
    int aux1 = ledEnemigo - ledJugador;
    int caso1 = fabs(aux1);
    int aux2 = caso1 - 8;
    int caso2 = fabs(aux2);
    if (caso1 == 0 || caso2 == 0) {
        return 0;
    }
    if (caso1 < caso2) {
        if (ledJugador > ledEnemigo) {
            return 1;
        } else {
            return -1;
        }
    } else if (caso2 < caso1) {
        if (ledJugador > ledEnemigo) {
            return -1;
        } else {
            return 1;
        }
    } else if (caso1 == caso2) {
        if (ledJugador > ledEnemigo) {
            return 1;
        } else {
            return -1;
        }
    }
}

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

int spawn(int posicionJugador) {
    if (posicionJugador < 5) {
        return posicionJugador + 3;
    } else if (posicionJugador == 5) {
        return 2;
    } else if (posicionJugador == 6) {
        return 3;
    } else {
        return 4;
    }
}

/** 
  @Function
    void enemigo(void *p_param)

  @Summary
    Tarea principal que controla la posicion del enemigo y las condiciones para perder.

  @Description
     Tarea que controla si se perdió el juego, en base a los recursos compartidos con la tarea de la posición del jugador.
     Si la posicion del enemigo es igual a la del jugador entonces se termina el juego.
  
 */

void enemigo(void *p_param) {
    app_register_t ledEnemigo;
    app_register_t ledEnemigoAnterior;
    int posicionActual;
    ledEnemigoAnterior.color = 4;
    ledEnemigo.color = 1;
    if (semaforo != NULL) {
        if (xSemaphoreTake(semaforo, (TickType_t) portMAX_DELAY) == pdTRUE) {
            ledEnemigo.led = spawn(ledActualJugador);
            xSemaphoreGive(semaforo);
        } else {
        }
    }
    while (1) {
        if (semaforo != NULL) {
            if (xSemaphoreTake(semaforo, (TickType_t) 100) == pdTRUE) {
                //BUZZ_CTRL_SetHigh();
                aumentarDificultad();
                ledEnemigoAnterior.led = ledEnemigo.led;
                posicionActual = ledEnemigo.led;
                if (proximoMovimiento2 == 0 || (ledEnemigo.led == ledActualJugador)) {
                    estaJugando = false;
                }
                if (estaJugando) {
                    ledEnemigo.led = posicionActual + (proximoMovimiento2(ledActualJugador, posicionActual));

                    if (ledEnemigo.led == 8) {
                        ledEnemigo.led = 0;
                        posicionActual = 0;
                    }
                    if (ledEnemigo.led == -1) {
                        ledEnemigo.led = 7;
                        posicionActual = 7;
                    }
                    encenderLED(ledEnemigo);
                    encenderLED(ledEnemigoAnterior);
                }
                xSemaphoreGive(semaforo);
            } else {// SI NO SE PUDO OBTENER EL SEMAFORO
                vTaskDelay(pdMS_TO_TICKS(1));
            }
        }
        //BUZZ_CTRL_SetLow();
        vTaskDelay(pdMS_TO_TICKS(tiempoDificultad));
    }
}


/* *****************************************************************************
 End of File
 */
