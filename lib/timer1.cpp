#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer1.h"



void Timer1::initialisation(){
    cli();
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    sei();
}

void Timer1::modifyPwm(uint16_t durationA, uint16_t durationB) const {
    OCR1A = durationA ;
    OCR1B = durationB ;
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

void Timer1::startTimer( uint16_t duration, bool isCTC) {
    TCNT1 = 0;
    OCR1A = duration;
    TCCR1A = 0 ;
    TCCR1B = (1 << CS12) | (1 << CS10);
    //TCCR1B &= !(1 << CS11);
    if (isCTC) { TCCR1B |= (1 << WGM12);}
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A) ;
}

void Timer1::stopTimer() {
    TCCR1B = 0;
}