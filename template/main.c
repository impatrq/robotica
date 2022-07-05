#include <stdio.h>
#include "pico/stdlib.h"

/* Defino pines para usar de trigger y echo */
#define TRIGGER 7
#define ECHO    8

/* Funciones para infrarojo */

/*
 *  @brief  Inicializa un sensor infrarojo en el pin indicado
 *  @param  pin: numero de pin conectado al infrarojo
 */
static inline void infrarojo_init(uint8_t pin){
    gpio_init(pin);
    gpio_set_dir(pin, false);
}

/*
 *  @brief  Obtiene el valor que entregue el infrarojo
 *  @param  pin: numero de pin conectado al infrarojo
 *  @return true si la luz volvio, false si no
 */
static inline bool infrarojo_get(uint8_t pin) { return !gpio_get(pin); }

/* Prototipos para funciones de ultrasonido */
void ultrasonico_init(uint8_t trigger, uint8_t echo);
float ultrasonico_get_distance_cm(uint8_t trigger, uint8_t echo);

/*
 *  @brief  Programa principal
 */
int main(void) {

    stdio_init_all();

    /* Inicializacion del ultrasonico */
    ultrasonico_init(TRIGGER, ECHO);

    while(1) {
        /* Obtengo la distancia en cm */
        float distance = ultrasonico_get_distance_cm(TRIGGER, ECHO);
        /* Imprimo el valor en consola */
        printf("Distancia: %.2f cm\r\n", distance);
        /* Demora */
        sleep_ms(1000);
    }
}

/*
 *  @brief  Inicializa los pines del ultrasonico
 *
 *  @param  trigger: numero de GP para usar de TRIGGER
 *  @param  echo: numero de GP para usar de ECHO
 */
void ultrasonico_init(uint8_t trigger, uint8_t echo) {
    /* Habilito el pin de Trigger */
    gpio_init(trigger);  
    /* Configuro el Trigger como salida */
    gpio_set_dir(trigger, true);
    /* Pongo un 0 en el pin de Trigger */
    gpio_put(trigger, false);
    /* Habilito el pin de Echo */
    gpio_init(echo);
    /* Configuro el Echo como entrada */
    gpio_set_dir(echo, false);
}

/*
 *  @brief  Obtiene la distancia en cm
 *  
 *  @param  trigger: numero de GP para usar de TRIGGER
 *  @param  echo: numero de GP para usar de ECHO
 * 
 *  @return distancia en cm
 */
float ultrasonico_get_distance_cm(uint8_t trigger, uint8_t echo) {
    /* Escribo un 1 en el Trigger */
    gpio_put(trigger, true);
    /* Espero 10 us con el pulso encendido */
    sleep_us(10);
    /* Escribo un 0 en el Trigger */
    gpio_put(trigger, false);
    /* Espero a que el pulso llegue al Echo */
    while(!gpio_get(echo));
    /* Mido el tiempo de cuando llega el pulso */
    absolute_time_t from = get_absolute_time();
    /* Espero a que el pulso del Echo baje a cero */
    while(gpio_get(echo));
    /* Mido el tiempo cuando termina el pulso */
    absolute_time_t to = get_absolute_time();
    /* Saco la diferencia de tiempo (el ancho del pulso) en us */
    int64_t pulse_width = absolute_time_diff_us(from, to);
    /* Calculo la distancia y la devuelvo */
    return pulse_width / 59.0;
}