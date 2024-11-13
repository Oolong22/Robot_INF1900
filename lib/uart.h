#include <avr/io.h>

#ifndef UART_H
#define UART_H

class UART {
public:
    void initialisationUART ( void );
    void transmissionUART ( unsigned char data );
    //void transmissionUART ( const char* data );
    void transmissionUARTstring (char* text);
    unsigned char USART_Receive( void );
};

#endif /* UART_H */