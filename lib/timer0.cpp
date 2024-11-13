#include "timer0.h"  // Update the header name

void Timer0::initialisation(){
    cli();
    DDRD &= ~(1 << DDD2);
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00) | (1 << ISC01);
    sei();
}

void Timer0::modifyPwm(uint16_t durationA) const {
    TCNT0 = 0;
    OCR0B = durationA;
    TCCR0A = (1 << COM0A0) | (1 << COM0B0) | (1 << WGM01) ;
    TCCR0B = (1 << CS02); //Prescaler 256
}

void Timer0::startTimer(uint16_t duration, bool isCTC) {
    TCNT0 = 0;  // Reset Timer0 counter
    OCR0A = duration;
    TCCR0A = 0; 
    TCCR0B = (1 << CS02); // Prescaler of 256 
    if (isCTC) { TCCR0A |= (1 << WGM01);} // Set CTC mode if needed
    TIMSK0 = (1 << OCIE0A); // Enable Timer0 Compare Match A interrupt
}

void Timer0::stopTimer() {
    DDRB &= ~(1 << DDB4) & ~(1 << DDB5) & ~(1 << DDB6);
}

void Timer0::send38kHz() {
    // DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5) | (1 << DDB6);
    DDRB |= (1 << DDB4);
    DDRB &= ~(1 << DDB2);
    TCNT0 = 0;
    OCR0A = 104;
    TCCR0A = (1 << COM0A0) | (1 << COM0B0) | (1 << WGM01) ;
    TCCR0B = (1 << CS00); //Prescaler 256
    TCCR0B &= ~(1 << CS02); //Prescaler 256
    TCCR0B &= ~(1 << CS01); //Prescaler 256
}
