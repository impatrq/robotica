#include "bt.h"

 /*
 *  @param  tx: numero del pin tx de la pico 
 *  @param  rx: numero del pin rx de la pico
 */

void uart_start(uint8_t tx, uint8_t rx){


    /*incio el bus UART a 9600 baudios */
    uart_init(uart_id, 9600);   
    /*seteo pines como UART */
    gpio_set_function(tx,GPIO_FUNC_UART); 
    gpio_set_function(rx, GPIO_FUNC_UART);
    
}
