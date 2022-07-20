/* ************************************************************************** */
/** 

  @File Name
    jugador.c

  @Summary
 Tarea que controla la posición del jugador.

  @Description
 Esta tarea simula la posición de una pelotita utilizando el acelerómetro integrado para calcular velocidad en X e Y. 
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */

/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "jugador.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
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

int ledActualJugador;


/** arrayLEDS

  @Summary
    Arreglo con los 8 Leds de la placa.
    
  @Description
 Este arreglo almacena los datos de los leds para encender en la placa, es un recurso compartido entre la tarea del jugador
  y la tarea del enemigo.
   
  @Remarks
    Protegido por un semáforo. 
 */

ws2812_t arrayLEDS[8];

/** semaforo

  @Summary
    Handler del semáforo.
    
  @Description
    Se utiliza este semáforo para controlar que tarea tiene acceso a los recursos compartidos.
   
 */

SemaphoreHandle_t semaforo;





/* ************************************************************************** */
/* ************************************************************************** */
// Section: Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/** 
  @Function
    void crearSemaforo();

  @Summary
 Crea el semáforo.

 */

void crearSemaforo() {
    semaforo = xSemaphoreCreateMutex();
}

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

void encenderLED(app_register_t unLed) {
    if (unLed.color == 0) {
        arrayLEDS[unLed.led] = WHITE;
    }
    if (unLed.color == 1) {
        arrayLEDS[unLed.led] = RED;
    }
    if (unLed.color == 2) {
        arrayLEDS[unLed.led] = BLUE;
    }
    if (unLed.color == 3) {
        arrayLEDS[unLed.led] = GREEN;
    }
    if (unLed.color == 4) {
        arrayLEDS[unLed.led] = BLACK;
    }
    if (unLed.color == 5) {
        arrayLEDS[unLed.led] = VIOLET;
    }
    if (unLed.color == 6) {
        arrayLEDS[unLed.led] = BROWN;
    }
    if (unLed.color == 7) {
        arrayLEDS[unLed.led] = GREY;
    }
    if (unLed.color == 8) {
        arrayLEDS[unLed.led] = PINK;
    }
    if (unLed.color == 9) {
        arrayLEDS[unLed.led] = YELLOW;
    }
    if (unLed.color == 10) {
        arrayLEDS[unLed.led] = ORANGE;
    }
    WS2812_send(arrayLEDS, 8);
}

/** 
  @Function
 apagarTodos();

  @Summary
 Apaga todos los LEDs de la placa.
 */

void apagarTodos() {
    app_register_t ledApagar;
    int i;
    ledApagar.color = 4;
    for (i = 0; i < 8; i++) {
        ledApagar.led = i;
        encenderLED(ledApagar);
    }
}



/** 
  @Function
 void jugador(void *p_param);

  @Summary
    Función principal para controlar la posición del jugador.

  @Description
    Es una tarea que cada 1 ms, actualiza la posición del jugador en base al movimiento realizado en la placa, capturado por 
    el acelerómetro
 */

void jugador(void *p_param) {
    crearSemaforo();
    const int tiempo = 1;
    const float valor = 0.25;
    float radio;
    float angulo;
    float anguloGrados;
    float aceleracionX;
    float aceleracionY;
    float velocidadInicialX = 0;
    float velocidadInicialY = 0;
    float velocidadX;
    float velocidadY;
    float posicionX;
    float posicionY;
    uint32_t seed;
    seed = _CP0_GET_COUNT();
    srand(seed);
    float posicionInicialX = rand() % 10 + (-5);
    float posicionInicialY = rand() % 10 + (-5);
    app_register_t ledNuevo;
    ledNuevo.color = 0;
    ledNuevo.led = 0; 
    app_register_t ledAnterior;
    ledAnterior.color = 4;
    Accel_t accel;

    while (1) {
        if (ACCEL_init()) {
            if (ACCEL_GetAccel(&accel)) {
                if (posicionX > 0) {
                } else {
                }
                //Aceleracion
                aceleracionX = accel.Accel_X * valor;
                aceleracionY = accel.Accel_Y * valor;
                //Velocidad
                velocidadX = (velocidadInicialX + (aceleracionX * tiempo)) * valor;
                velocidadY = (velocidadInicialY + (aceleracionY * tiempo)) * valor;
                //Posicion MRU
                posicionX = posicionInicialX + velocidadX*tiempo;
                posicionY = posicionInicialY + velocidadY*tiempo;
                //remplazando
                velocidadInicialX = velocidadX;
                velocidadInicialY = velocidadY;
                posicionInicialX = posicionX;
                posicionInicialY = posicionY;
                // Cartesiana a Polar
                float paso = (posicionX * posicionX)+(posicionY * posicionY);
                radio = sqrt(paso);
                angulo = atan2f(posicionY, posicionX); //arco tangente con la posicicion
                anguloGrados = (angulo * 180) / 3.141592654; //paso a grados

                if (radio >= 20) { //limito el radio, en caso de ser mayor a mi maximo, calculo las nuevas posiciones con el maximo
                        posicionInicialX = 20 * cos(angulo); 
                        posicionInicialY = 20 * sin(angulo); 
                        radio = 20;
                        velocidadX = 0;
                        velocidadY = 0;
                        aceleracionX = 0;
                        aceleracionY = 0;
                    
                }
                //prender leds
                if (semaforo != NULL) {
                    if (xSemaphoreTake(semaforo, (TickType_t) 10) == pdTRUE) {

                        if (anguloGrados > 0 && anguloGrados <= 45) { //LED
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 4;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 4;

                        } else if (anguloGrados > 45 && anguloGrados <= 90) { //LED 3
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 3;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 3;

                        } else if (anguloGrados > 90 && anguloGrados <= 135) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 2;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 2;

                        } else if (anguloGrados > 135 && anguloGrados <= 180) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 1;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 1;

                        }//NEGATIVOS
                        else if (anguloGrados > -180 && anguloGrados <= -135) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 0;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 0;

                        } else if (anguloGrados > -135 && anguloGrados <= -90) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 7;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 7;

                        } else if (anguloGrados >-90 && anguloGrados <= -45) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 6;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 6;

                        } else if (anguloGrados > -45 && anguloGrados < 0) {
                            ledAnterior.led = ledNuevo.led;
                            ledNuevo.led = 5;
                            encenderLED(ledNuevo);
                            encenderLED(ledAnterior);
                            ledActualJugador = 5;
                        }
                        xSemaphoreGive(semaforo);
                    } else {// no se pudo obtener el semaforo.                 
                    }
                }
                vTaskDelay(pdMS_TO_TICKS(tiempo));
            }
        }
    }
}

/* *****************************************************************************
 End of File
 */
