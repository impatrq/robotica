#include "l298.h"


/*
 *  @brief  Inicializa los pines para trabajar con un motor de DC
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_init(l298_t l298) {
    /* Habilito salidas */
    gpio_init_mask(1 << l298.forward | 1 << l298.reverse);
    gpio_set_dir_out_masked(1 << l298.forward | 1 << l298.reverse);
    /* Seteo pines como PWM */
    gpio_set_function(l298.en, GPIO_FUNC_PWM);
    /* Consigo los slices de los pines */
    uint slice = pwm_gpio_to_slice_num(l298.en);
    /* Obtengo configuracion por defecto de PWM */
    pwm_config config = pwm_get_default_config();
    /* Inicializo el slice */
    pwm_init(slice, &config, true);
    /* Arranco con 0% de ancho de pulso */
    pwm_set_gpio_level(l298.en, 0);
}

/*
 *  @brief  Indica al motor de que vaya hacia adelante
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_forward(l298_t l298) {
    /* Apago el pin de reverse */
    gpio_put(l298.reverse, false);
    /* Prendo el pin de forward */
    gpio_put(l298.forward, true);
    /* 100% de ancho de pulso para el pin de enable */
    pwm_set_gpio_level(l298.en, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 */
void motor_reverse(l298_t l298) {
    /* Apago el pin de forward */
    gpio_put(l298.forward, false);
    /* Prendo el pin de reverse */
    gpio_put(l298.reverse, true);
    /* 100% de ancho de pulso para el pin de enable */
    pwm_set_gpio_level(l298.en, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia adelante parcialmente
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_forward_partial(l298_t l298, uint8_t partial) {
    /* Apago el pin de reverse */
    gpio_put(l298.reverse, false);
    /* Prendo el pin de forward */
    gpio_put(l298.forward, true);
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de avance */
    pwm_set_gpio_level(l298.en, duty);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras parcialmente
 *  @param  pin_forwart: numero de pin que controla la direccion de avance
 *  @param  pin_reverse: numero de pin que controla la direccion de reversa
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_reverse_partial(l298_t l298, uint8_t partial) {
    /* Apago el pin de forward */
    gpio_put(l298.forward, false);
    /* Prendo el pin de reverse */
    gpio_put(l298.reverse, true);
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de reversa */
    pwm_set_gpio_level(l298.en, duty);
}