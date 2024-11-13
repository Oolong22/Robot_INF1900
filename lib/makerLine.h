#pragma once

#include <avr/io.h>
#include "robotMovement.h"
#include "setLed.h"
#include "timer0.h"
#include "segment.h"

#ifndef MAKERLINE_H
#define MAKERLINE_H

class MakerLine : public RobotMovement {
public:
    void init() {
        DDRA &= ~(1 << DDA0) & ~(1 << DDA1) & ~(1 << DDA2) & ~(1 << DDA3) & ~(1 << DDA4);
    }
    void followLine(uint8_t speed, uint8_t turnSpeed, Timer0& timer0);
    void correctDeviation(uint8_t speed);
    void delayWithCorrection(uint8_t speed);
    void delayWithCorrectionPrecise(uint16_t delay, uint8_t speed);
    void debounce(bool state);
    void lineMeasurement(uint8_t speed, Timer0& timer0, uint16_t position, bool isDown);
    void lineMovement(uint8_t speed, uint8_t turnSpeed, Timer0& timer0, uint16_t position, bool isDown);
    void turnCorner(uint8_t speed, uint8_t turnSpeed);
    void correctDeviationHard(uint8_t speed);

    Segment segmentList[6];
private:
    SetLed led = SetLed(&PORTC, PORTC2, PORTC3);
    uint8_t lineCounter = 0;
};

#endif /* MAKERLINE_H */