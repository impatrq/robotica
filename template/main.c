#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

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

/* Prototipos para funciones de motores */
void motor_init(uint8_t pin_forward, uint8_t pin_reverse);
void motor_forward(uint8_t pin_forward, uint8_t pin_reverse);
void motor_reverse(uint8_t pin_forward, uint8_t pin_reverse);
void motor_forward_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial);
void motor_reverse_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial);

/*
 *  @brief  Programa principal
 */
int main(void) {

    stdio_init_all();

    while(1) {

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

/*
 *  @brief  Inicializa los pines para trabajar con un motor de DC
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_init(uint8_t pin_forward, uint8_t pin_reverse) {
    /* Seteo pines como PWM */
    gpio_set_function(pin_forward, GPIO_FUNC_PWM);
    gpio_set_function(pin_reverse, GPIO_FUNC_PWM);
    /* Consigo los slices de los pines */
    uint slice_pin_forward = pwm_gpio_to_slice_num(pin_forward);
    uint slice_pin_reverse = pwm_gpio_to_slice_num(pin_forward);
    /* Obtengo configuracion por defecto de PWM */
    pwm_config config = pwm_get_default_config();
    /* Inicializo ambos slices */
    pwm_init(slice_pin_forward, &config, true);
    pwm_init(slice_pin_reverse, &config, true);
    /* Arranco con 0% de ancho de pulso */
    pwm_set_gpio_level(pin_forward, 0);
    pwm_set_gpio_level(pin_reverse, 0);
}

/*
 *  @brief  Indica al motor de que vaya hacia adelante
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_forward(uint8_t pin_forward, uint8_t pin_reverse) {
    /* 0% de ancho de pulso para el pin de reversa */
    pwm_set_gpio_level(pin_reverse, 0);
    /* 100% de ancho de pulso para el pin de avance */
    pwm_set_gpio_level(pin_forward, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_reverse(uint8_t pin_forward, uint8_t pin_reverse) {
    /* 0% de ancho de pulso para el pin de avance */
    pwm_set_gpio_level(pin_forward, 0);
    /* 100% de ancho de pulso para el pin de reversa */
    pwm_set_gpio_level(pin_reverse, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia adelante parcialmente
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_forward_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial) {
    /* 0% de ancho de pulso para el pin de reversa */
    pwm_set_gpio_level(pin_reverse, 0);
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de avance */
    pwm_set_gpio_level(pin_forward, duty);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras parcialmente
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_reverse_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial) {
    /* 0% de ancho de pulso para el pin de avance */
    pwm_set_gpio_level(pin_forward, 0);
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de reversa */
    pwm_set_gpio_level(pin_reverse, duty);
}