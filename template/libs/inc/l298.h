#ifndef _L298_H_
#define _L298_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"

typedef struct {
    uint8_t forward;
    uint8_t reverse;
    uint8_t en;
} l298_t;

/* Prototipos para funciones de motores */
void motor_init(l298_t l298);
void motor_forward(l298_t l298);
void motor_reverse(l298_t l298);
void motor_forward_partial(l298_t l298, uint8_t partial);
void motor_reverse_partial(l298_t l298, uint8_t partial);

#endif  /* _L298_H */