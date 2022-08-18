#include "l298.h"


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