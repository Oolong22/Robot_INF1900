#include "uart.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "debug.h"

void sendString(char* donnee) {
    UART uart;
    uart.initialisationUART() ;
    uint8_t nCharacters = strlen(donnee);
    for (uint8_t i = 0; i < nCharacters; i++) {
        uart.transmissionUART( donnee[i] ); 
        _delay_ms(5);
    }
}

void sendString(uint8_t donnee) {
    UART uart;
    uart.initialisationUART();
    uart.transmissionUART(donnee);
    _delay_ms(5);
}