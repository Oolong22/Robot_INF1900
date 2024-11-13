#ifndef TIMER0_H
#define TIMER0_H

#include <util/delay.h>
#include <avr/interrupt.h>

class Timer0 {
public:
    void initialisation();
    void modifyPwm(uint16_t durationA) const;
    void startTimer(uint16_t duration, bool isCTC);
    void stopTimer();
    void send38kHz();
};

#endif
