#ifndef _BT_H_
#define _BT_H_

#include "pico/stdlib.h"
#include "hardware/uart.h"
/*defino que bus de uart voy a inicializar */
#define uart_id uart0

/* protitipo para funcion serial*/
void uart_start(uint8_t tx, uint8_t rx);

#endif  /* _BT_H_ */
