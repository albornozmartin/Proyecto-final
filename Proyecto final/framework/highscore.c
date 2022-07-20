/* ************************************************************************** */
/**
  @File Name
 highscore.c

  @Summary
    Controla el modo highscore.

  @Description
    Controla el inicio del juego, el guardado de memoria y los modos.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */


#include "highscore.h"
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/** estaJugando

  @Summary
    Booleano que indica si se está jugando o no.
 */
bool estaJugando;

/** puntuación

  @Summary
    Entero que contabiliza la cantidad de puntos que lleva el jugador.
 */
int puntuacion = 0;

/** tareaJugador

  @Summary
     Handler para controlar la tarea jugador.
 */
TaskHandle_t tareaJugador;


/** tareaEnemigo

  @Summary
    Handler para controlar la tarea enemigo.
 */
TaskHandle_t tareaEnemigo;


/** tareaPuntuacion

  @Summary
    Handler para controlar la tarea puntuacion.
 */
TaskHandle_t tareaPuntuacion;


/** handlerDelTimer

  @Summary
    Handler para controlar el timer del botón s2.
 */
xTimerHandle handlerDelTimer;


/** arrayPuntuacion

  @Summary
 Array utilizado para controlar los LED que se deben encender para mostrar la puntuación.
 */
ws2812_t arrayPuntuacion[8];


/** aMostrar

@Summary
 Datos obtenidos de la memoria flash.
 */
uint32_t aMostrar;


// Pagina vacia, y variables utilizadas para levantar y guardar los datos en memoria

static const uint32_t __attribute((space(prog), aligned(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS))) paginaParaGuardar[FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS / 2];
uint32_t flash_storage_address, flashOffset, readData;
uint16_t result;
uint32_t write_data[2] = {0};
uint32_t read_data[2] = {0};
uint32_t salida[2] = {0};

int scoreParaMostrar;
bool contar = true;

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */


/* ************************************************************************** */

/** 
  @Function
void encenderPuntuacion(app_register_t unLed) 

  @Summary
     función utilizada para encender los Leds de la puntuación.
  
    @Parameters
    @app_regeister_t  unLed led a encender.
    
 */


void encenderPuntuacion(app_register_t unLed) {
    if (unLed.color == 0) {
        arrayPuntuacion[unLed.led] = WHITE;
    }
    if (unLed.color == 1) {
        arrayPuntuacion[unLed.led] = RED;
    }
    if (unLed.color == 2) {
        arrayPuntuacion[unLed.led] = BLUE;
    }
    if (unLed.color == 3) {
        arrayPuntuacion[unLed.led] = GREEN;
    }
    if (unLed.color == 4) {
        arrayPuntuacion[unLed.led] = BLACK;
    }
    if (unLed.color == 5) {
        arrayPuntuacion[unLed.led] = VIOLET;
    }
    if (unLed.color == 6) {
        arrayPuntuacion[unLed.led] = BROWN;
    }
    if (unLed.color == 7) {
        arrayPuntuacion[unLed.led] = GREY;
    }
    if (unLed.color == 8) {
        arrayPuntuacion[unLed.led] = PINK;
    }
    if (unLed.color == 9) {
        arrayPuntuacion[unLed.led] = YELLOW;
    }
    if (unLed.color == 10) {
        arrayPuntuacion[unLed.led] = ORANGE;
    }
    WS2812_send(arrayPuntuacion, 8);
}

/** 
  @Function
void mostrarPuntuacion(int puntuacion)

  @Summary
 Según la puntuación, encenderá los leds 2, 3 y 5 de acuerdo al color correspondiente al número.

    @Parameters
    @int puntuacion 

 */

void mostrarPuntuacion(int puntuacion) {
    int millares = puntuacion / 1000;
    int centenas = (puntuacion - (millares * 1000)) / 100;
    int decenas = (puntuacion - (millares * 1000 + centenas * 100)) / 10;
    int unidades = puntuacion - (millares * 1000 + centenas * 100 + decenas * 10);
    app_register_t led0;
    led0.led = 2;
    app_register_t led7;
    led7.led = 3;
    app_register_t led6;
    led6.led = 4;
    if (millares > 0) {
        centenas = 9;
        decenas = 9;
        unidades = 9;
    }

    if (centenas == 0) {
        led0.color = 0; //blanco
    } else if (centenas == 1) {
        led0.color = 9; //amarillo
    } else if (centenas == 2) {
        led0.color = 3; //verde
    } else if (centenas == 3) {
        led0.color = 2; //azul
    } else if (centenas == 4) {
        led0.color = 5; //violeta
    } else if (centenas == 5) {
        led0.color = 1; //rojo
    } else if (centenas == 6) {
        led0.color = 10; //naranja
    } else if (centenas == 7) {
        led0.color = 6; //marron
    } else if (centenas == 8) {
        led0.color = 7; //gris
    } else if (centenas == 9) {
        led0.color = 8; //rosado
    }
    if (decenas == 0) {
        led7.color = 0; //blanco
    } else if (decenas == 1) {
        led7.color = 9; //amarillo
    } else if (decenas == 2) {
        led7.color = 3; //verde
    } else if (decenas == 3) {
        led7.color = 2; //azul
    } else if (decenas == 4) {
        led7.color = 5; //violeta
    } else if (decenas == 5) {
        led7.color = 1; //rojo
    } else if (decenas == 6) {
        led7.color = 10; //naranja
    } else if (decenas == 7) {
        led7.color = 6; //marron
    } else if (decenas == 8) {
        led7.color = 7; //gris
    } else if (decenas == 9) {
        led7.color = 8; //rosado
    }
    if (unidades == 0) {
        led6.color = 0; //blanco
    } else if (unidades == 1) {
        led6.color = 9; //amarillo
    } else if (unidades == 2) {
        led6.color = 3; //verde
    } else if (unidades == 3) {
        led6.color = 2; //azul
    } else if (unidades == 4) {
        led6.color = 5; //violeta
    } else if (unidades == 5) {
        led6.color = 1; //rojo
    } else if (unidades == 6) {
        led6.color = 10; //naranja
    } else if (unidades == 7) {
        led6.color = 6; //marron
    } else if (unidades == 8) {
        led6.color = 7; //gris
    } else if (unidades == 9) {
        led6.color = 8; //rosado
    }
    encenderLED(led6);
    _nop();
    _nop();
    encenderLED(led7);
    _nop();
    _nop();
    encenderLED(led0);
    _nop();
    _nop();
}

/** 
  @Function
void guardarEnMemoria()

  @Summary
 Guarda la puntuación en la memoria no volatil.

 */

void guardarEnMemoria() {
    flash_storage_address = (uint32_t) paginaParaGuardar;
    //key para desbloquear memoria flash
    FLASH_Unlock(FLASH_UNLOCK_KEY);
    //borra la pagina 
    result = FLASH_ErasePage(flash_storage_address);
    //guarda informacion en 4 lugares
    write_data[0] = scoreParaMostrar;
    write_data[1] = 0;
    result = FLASH_WriteDoubleWord(flash_storage_address, write_data[0], write_data[1]);
    //bloquea la memoria flash
    FLASH_Lock();
}

/** 
  @Function
    void borrarMemoria() 

  @Summary
     Remplaza lo que haya en memoria por un 0;

 */

void borrarMemoria() {
    flash_storage_address = (uint32_t) paginaParaGuardar;
    //key para desbloquear memoria flash
    FLASH_Unlock(FLASH_UNLOCK_KEY);
    //borra la pagina 
    result = FLASH_ErasePage(flash_storage_address);
    // Write 32 bit Data to the first DWORD locations.
    //guarda informacion en 4 lugares
    write_data[0] = 0;
    write_data[1] = 0;
    result = FLASH_WriteDoubleWord(flash_storage_address, write_data[0], write_data[1]);
    //bloquea la memoria flash
    FLASH_Lock();
}


/** 
  @Function
uint32_t leerEnMemoria()

  @Summary
    Indica hacia donde mover el led del enemigo.


 */

/** 
  @Function
uint32_t leerEnMemoria()

  @Summary
 Retorna lo que haya en memoria.

 */

uint32_t leerEnMemoria() {
    flash_storage_address = (uint32_t) paginaParaGuardar;
    read_data[0] = FLASH_ReadWord(flash_storage_address);
    return read_data[0];
}



/** 
  @Function
void modoJuego(void *p_param) 

  @Summary
 Tarea inicial del juego.

  @Description
 Controla todos los modos del juego y permite guardar en memoria no volatil la puntuación máxima.
 */

void modoJuego(void *p_param) {

    
    BTN1_SetDigitalInput();
    MODO modo = HIGHSCORE;
    while (1) {
        switch (modo) {
            case(HIGHSCORE):
                aMostrar = leerEnMemoria();
                mostrarPuntuacion(aMostrar);
                if (BTN1_GetValue() && !BTN2_GetValue()) {
                    apagarTodos();
                    contar = true;
                    xTaskCreate(jugador, "task1", configMINIMAL_STACK_SIZE + 300, NULL, tskIDLE_PRIORITY + 3, &tareaJugador);
                    xTaskCreate(enemigo, "task2", configMINIMAL_STACK_SIZE + 300, NULL, tskIDLE_PRIORITY + 2, &tareaEnemigo);
                    xTaskCreate(contarPuntuacion, "task3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &tareaPuntuacion);
                    modo = JUEGO;
                }
                if (BTN2_GetValue()) {
                    vTaskDelay(pdMS_TO_TICKS(3000));
                    if (BTN2_GetValue()) {
                        borrarMemoria();
                    }
                }
                break;
            case (JUEGO):
                estaJugando = true;
                vTaskDelay(pdMS_TO_TICKS(200));
                if (BTN1_GetValue()) {
                    vTaskDelete(tareaJugador);
                    vTaskDelete(tareaEnemigo);
                    vTaskDelete(tareaPuntuacion);
                    apagarTodos();
                    puntuacion = 0;
                    xTaskCreate(jugador, "task1", configMINIMAL_STACK_SIZE + 300, NULL, tskIDLE_PRIORITY + 3, &tareaJugador);
                    xTaskCreate(enemigo, "task2", configMINIMAL_STACK_SIZE + 300, NULL, tskIDLE_PRIORITY + 2, &tareaEnemigo);
                    xTaskCreate(contarPuntuacion, "task3", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &tareaPuntuacion);
                }
                if (!estaJugando) {
                    modo = FIN;
                }
                break;
                //jugar
            case(FIN):
                //perdiste
                contar = false;
                
                scoreParaMostrar = puntuacion;
                apagarTodos();
                
                vTaskDelete(tareaJugador);
                vTaskDelete(tareaEnemigo);
                vTaskDelete(tareaPuntuacion);

                mostrarPuntuacion(scoreParaMostrar);
                if (scoreParaMostrar > aMostrar) {
                    guardarEnMemoria();
                }
                puntuacion = 0;
                vTaskDelay(pdMS_TO_TICKS(2500));
                modo = HIGHSCORE;
                break;
                vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}


/* *****************************************************************************
 End of File
 */
