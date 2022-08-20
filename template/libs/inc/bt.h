#ifndef _BT_H_
#define _BT_H_

#include "pico/stdlib.h"
#include "hardware/uart.h"
#define uart_id uart0

void uart_start(uint8_t tx, uint8_t rx);

#endif  /* _BT_H_ */
