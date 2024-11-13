#include <avr/io.h>

#ifndef TIMER1_H
#define TIMER1_H

class Timer1 {
public:
    void initialisation();
    void modifyPwm(uint16_t durationA, uint16_t durationB) const;
    void startTimer( uint16_t duration = 0, bool isCTC = false );
    void stopTimer();
};

#endif /* TIMER1_H */