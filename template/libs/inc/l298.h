#ifndef _L298_H_
#define _L298_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"

/* Prototipos para funciones de motores */
void motor_init(uint8_t pin_forward, uint8_t pin_reverse);
void motor_forward(uint8_t pin_forward, uint8_t pin_reverse);
void motor_reverse(uint8_t pin_forward, uint8_t pin_reverse);
void motor_forward_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial);
void motor_reverse_partial(uint8_t pin_forward, uint8_t pin_reverse, uint8_t partial);

#endif  /* _L298_H */