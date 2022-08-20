#include "bt.h"


void uart_start( uint8_t tx, uint8_t rx){

    uart_init(uart_id, 9600);
    gpio_set_function(tx,GPIO_FUNC_UART);
    gpio_set_function(rx, GPIO_FUNC_UART);
    
}
