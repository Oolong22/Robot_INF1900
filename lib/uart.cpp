#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

void UART::initialisationUART ( void ) {
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = (1 << RXC0) | (1 << TXC0) ;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) |  (1 << UCSZ00);
}

void UART::transmissionUART ( unsigned char data ) {
    while ( !( UCSR0A & (1<<UDRE0)) );
    UDR0 = data;
}

void UART::transmissionUARTstring (char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        transmissionUART(text[i]);
    }
}

// void UART::transmissionUART ( const char* data ) {
//     while ( !( UCSR0A & (1<<UDRE0)) );
//     UDR0 = data;
// }

unsigned char UART::USART_Receive( void ) {
    while ( !(UCSR0A & (1<<RXC0)) );
    return UDR0;
}