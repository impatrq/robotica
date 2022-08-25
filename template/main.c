#include <stdio.h>
#include "pico/stdlib.h"
#include "l298.h"
#include "infrarojo.h"
#include "ultrasonico.h"
#include "bt.h"

/*
 *  @brief  Programa principal
 */
int main(void) {

    stdio_init_all();

    const uint8_t TRIGGER = 0;
    const uint8_t ECHO = 1;

    const uint8_t INFRAROJO_FRENTE = 28;
    const uint8_t INFRAROJO_IZQUIERDA = 6;
    const uint8_t INFRAROJO_DERECHA = 27;

    const uint8_t MOTOR_IZQUIERDO_FORWARD = 13;
    const uint8_t MOTOR_IZQUIERDO_REVERSE = 14;
    const uint8_t MOTOR_IZQUIERDO_ENABLE = 15;

    const uint8_t MOTOR_DERECHO_FORWARD = 16;
    const uint8_t MOTOR_DERECHO_REVERSE = 17;
    const uint8_t MOTOR_DERECHO_ENABLE = 18;

    ultrasonico_init(TRIGGER, ECHO);
    infrarojo_init(INFRAROJO_FRENTE);
    infrarojo_init(INFRAROJO_DERECHA);
    infrarojo_init(INFRAROJO_IZQUIERDA);

    l298_t motor_izquierdo = { 
        MOTOR_IZQUIERDO_FORWARD,
        MOTOR_IZQUIERDO_REVERSE,
        MOTOR_IZQUIERDO_ENABLE
    };

    l298_t motor_derecho = {
        MOTOR_DERECHO_FORWARD,
        MOTOR_DERECHO_REVERSE,
        MOTOR_DERECHO_ENABLE
    };
    
    motor_init(motor_izquierdo);
    motor_init(motor_derecho);

    while(1) {

        float distance = ultrasonico_get_distance_cm(TRIGGER, ECHO);
        if(distance < 50) {
            motor_forward(motor_izquierdo);
            motor_forward(motor_derecho);
        }
    }
}
