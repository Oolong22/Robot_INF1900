#include <util/delay.h>
#include <avr/interrupt.h>
#include "setLed.h"

const int DEUX_CENT_MILLISECONDES = 200;

SetLed::SetLed(volatile uint8_t *port, uint8_t pin1, uint8_t pin2) {
    port_ = port;
    pin1_ = pin1;
    pin2_ = pin2;
}

void SetLed::black() {
    *port_ &= ~(1 << pin1_);
    *port_ &= ~(1 << pin2_);
}

void SetLed::green() {
    *port_ |= (1 << pin2_);
    *port_ &= ~(1 << pin1_);
}

void SetLed::red() {
    *port_ |= (1 << pin1_);
    *port_ &= ~(1 << pin2_);
}

void SetLed::amber() {
    green();
    _delay_ms(10);
    red();
    _delay_ms(10);
}


void SetLed::flashingGreen() {
    green();
    _delay_ms(DEUX_CENT_MILLISECONDES);
    black();
    _delay_ms(DEUX_CENT_MILLISECONDES);
}
